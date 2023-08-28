/* SPDX-License-Identifier: LGPL-3.0-or-later */

/*
 * Copyright (C) 2023 Perry Werneck <perry.werneck@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

 /**
  * @brief SMBIos data methods for linux.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <private/data.h>
 #include <stdexcept>
 #include <system_error>

 #include <unistd.h>

 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <cstring>
 #include <iostream>
 #include <sys/mman.h>

 using namespace std;

 namespace SMBios {

	struct File {

		uint8_t *ptr;
		size_t length;

		File(const char *filename, size_t length = 0) {

			int fd = open(filename,O_RDONLY);

			if(fd < 0) {
				throw std::system_error(errno,std::system_category(),filename);
			}

			struct stat statbuf;
			memset(&statbuf,0,sizeof(statbuf));

			if(fstat(fd, &statbuf) != 0) {
				int err = errno;
				::close(fd);
				throw std::system_error(err,std::system_category(),filename);
			}

			if(!statbuf.st_blksize) {
				statbuf.st_blksize = 4096;
			}

			if(!length) {
				length = statbuf.st_size;
			}

			ptr = new uint8_t[length+1];
			memset(ptr,0,length+1);

			size_t pos = 0;
			while(pos < length) {

				size_t blksize = (length-pos);
				if(blksize > (size_t) statbuf.st_blksize) {
					blksize = statbuf.st_blksize;
				}

				ssize_t bytes = read(fd,ptr+pos,blksize);

				if(bytes < 0) {
					if(errno != EINTR) {
						int err = errno;
						delete[] ptr;
						::close(fd);
						throw std::system_error(err,std::system_category(),filename);
					}
				} else if(bytes == 0) {
					throw runtime_error(string{"Unexpected EOF in '"}+filename+"'");
				} else {
					pos += bytes;
				}

			}
			this->length = pos;

			::close(fd);
		}

		~File() {
			delete[] ptr;
		}
	};

	static bool checksum(const uint8_t *buf, size_t len) {
		uint8_t sum = 0;
		for(size_t a = 0; a < len; a++)
			sum += buf[a];
		return (sum == 0);
	}

	Data::Data(const char *smbios_entry_point, const char *smbios_dmi_table) {

		// Get entry point
		File entry(smbios_entry_point);

		if(memcmp(entry.ptr,"_SM3_",5) == 0) {

			dmi.type = TYPE3;

			// Don't let checksum run beyond the buffer
			if (entry.ptr[0x06] > 0x20) {
				throw runtime_error("Invalid SMBios length");
			}

			if(!checksum(entry.ptr, entry.ptr[0x06])) {
				throw runtime_error("Chksum mismatch");
			}

			dmi.version = (entry.ptr[0x07] << 16) + (entry.ptr[0x08] << 8) + entry.ptr[0x09];
			dmi.base = QWORD(entry.ptr + 0x10);
			dmi.length = DWORD(entry.ptr + 0x0C);

		} else if(memcmp(entry.ptr,"_SM_",4) == 0) {

			dmi.type = TYPE1;

			// Don't let checksum run beyond the buffer
			if (entry.ptr[0x05] > 0x20) {
				throw runtime_error("Invalid SMBios length");
			}

			if (!checksum(entry.ptr, entry.ptr[0x05]) || memcmp(entry.ptr + 0x10, "_DMI_", 5) != 0 || !checksum(entry.ptr + 0x10, 0x0F)) {
				throw runtime_error("Chksum mismatch");
			}

			dmi.version = (entry.ptr[0x06] << 8) + entry.ptr[0x07];

			// Some BIOS report weird SMBIOS version, fix that up
			switch (dmi.version) {
			case 0x021F:
			case 0x0221:
				dmi.version = 0x0203;
				break;
			case 0x0233:
				dmi.version = 0x0206;
				break;
			}

			dmi.base = DWORD(entry.ptr + 0x18);
			dmi.length = WORD(entry.ptr + 0x16);
			dmi.num = WORD(entry.ptr + 0x1C);

		} else {

			throw runtime_error("Unexpected SMBios identifier");

		}

		//
		// Load SMBIOS Data
		//
		File data{smbios_dmi_table,dmi.length};

		if(data.length != dmi.length) {
			throw runtime_error(string{"Unexpected length in '"}+smbios_dmi_table+"'");
		}

		this->ptr = new uint8_t[dmi.length+1];
		this->ptr[dmi.length] = 0;
		memcpy(this->ptr,data.ptr,dmi.length);
	}

 }
