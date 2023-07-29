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

 #include <config.h>
 #include <private/smbios.h>
 #include <stdexcept>
 #include <system_error>

 #include <unistd.h>

 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <cstring>
 #include <iostream>

 using namespace std;

 #if defined(BIGENDIAN)

	#define WORD(x)		(uint16_t)	((x)[0] + ((x)[1] << 8))
	#define DWORD(x)	(uint32_t) ((x)[0] + ((x)[1] << 8) + ((x)[2] << 16) + ((x)[3] << 24))

 #else

	#define WORD(x)		(uint16_t)(*(const uint16_t *)(x))
	#define DWORD(x)	(uint32_t)(*(const uint32_t *)(x))
	#define QWORD(x)	(*(const uint64_t *)(x))

 #endif // BIGENDIAN

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

			if(!length) {
				struct stat statbuf;
				memset(&statbuf,0,sizeof(statbuf));

				if (fstat(fd, &statbuf) != 0) {
					int err = errno;
					::close(fd);
					throw std::system_error(err,std::system_category(),filename);
				}

				length = statbuf.st_size;
			}

			ptr = new uint8_t[length+1];
			memset(ptr,0,length+1);

			size_t pos = 0;
			while(pos < length) {

				ssize_t bytes = read(fd,ptr,(length-pos));

				if(bytes < 0) {
					if(errno != EINTR) {
						int err = errno;
						delete[] ptr;
						::close(fd);
						throw std::system_error(err,std::system_category(),filename);
					}
				} else if(bytes == 0) {
					break;

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

	Data::Data() {

		struct {
			Data::Type type = Invalid;
			uint64_t base = 0;
			uint32_t len = 0;
			uint16_t num = 0;
			uint32_t version = 0;
		} dmi;

		// Get entry point
		File entry("/sys/firmware/dmi/tables/smbios_entry_point");

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
			dmi.len = DWORD(entry.ptr + 0x0C);

		} else if(memcmp(entry.ptr,"_SM_",4) == 0) {

			dmi.type = TYPE1;

			// Don't let checksum run beyond the buffer
			if (entry.ptr[0x05] > 0x20) {
				throw runtime_error("Invalid SMBios length");
			}

			if (!checksum(entry.ptr, entry.ptr[0x05]) || memcmp(entry.ptr + 0x10, "_DMI_", 5) != 0 || !checksum(entry.ptr + 0x10, 0x0F)) {
				throw runtime_error("Chksum mismatch");
			}

			uint16_t ver = (entry.ptr[0x06] << 8) + entry.ptr[0x07];

			// Some BIOS report weird SMBIOS version, fix that up
			switch (ver) {
			case 0x021F:
			case 0x0221:
				ver = 0x0203;
				break;
			case 0x0233:
				ver = 0x0206;
				break;
			}

			dmi.base = DWORD(entry.ptr + 0x18);
			dmi.len = WORD(entry.ptr + 0x16);
			dmi.num = WORD(entry.ptr + 0x1C);
			dmi.version = (ver << 8);

		} else {

			throw runtime_error("Unexpected SMBios identifier");

		}

		// Get SMBIOS.
		File data("/sys/firmware/dmi/tables/DMI",dmi.len);

		if(data.length != dmi.len) {
			throw runtime_error("/sys/firmware/dmi/tables/DMI: Unexpected EOF");
		}

		this->length = dmi.len;
		this->ptr = new uint8_t[this->length+1];
		this->ptr[this->length] = 0;
		memcpy(this->ptr,data.ptr,this->length);

	}

 }
