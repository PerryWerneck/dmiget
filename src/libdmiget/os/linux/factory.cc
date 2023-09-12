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

 #include <unistd.h>
 #include <private/data.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <stdexcept>
 #include <system_error>
 #include <cstring>

 using namespace std;

 namespace SMBios {

	std::shared_ptr<Data> Data::factory() {

		if(access("/sys/firmware/dmi/tables/smbios_entry_point",R_OK) == 0 && access("/sys/firmware/dmi/tables/DMI",R_OK) == 0) {
			return make_shared<Data>("/sys/firmware/dmi/tables/smbios_entry_point","/sys/firmware/dmi/tables/DMI");
		}

		throw runtime_error("Unable to load SMBios data");
	}

	Data::~Data() {
		delete[] ptr;
	}

	std::shared_ptr<Data> Data::factory(const char *filename) {

		if(!(filename && *filename)) {
			return factory();
		}

		struct stat statbuf;
		if (stat(filename, &statbuf) != 0) {
			int err = errno;
			throw std::system_error(err,std::system_category(),filename);
		}

		if( (statbuf.st_mode & S_IFMT) == S_IFDIR) {
			string dirname{filename};
			return make_shared<Data>((dirname + "/smbios_entry_point").c_str(), (dirname + "/DMI").c_str());
		}

		int fd = open(filename,O_RDONLY);

		if(fd < 0) {
			throw std::system_error(errno,std::system_category(),filename);
		}

		size_t datalength = statbuf.st_size - 0x0020;

		uint8_t *buffer = new uint8_t[datalength+1];
		memset(buffer,0,datalength+1);

		uint8_t *ptr = buffer;

		if(lseek(fd,0x0020, SEEK_SET) != 0x0020) {
			::close(fd);
			throw std::runtime_error("Error positioning input file");
		}

		size_t pos = 0;
		while(pos < datalength) {

			auto bytes = read(fd,ptr,(datalength - pos));

			if(bytes < 0) {
				if(errno != EINTR) {
					int err = errno;
					delete[] buffer;
					::close(fd);
					throw std::system_error(err,std::system_category(),filename);
				}
			} else if(bytes == 0) {
				break;

			} else {
				ptr += bytes;
				pos += bytes;
			}

		}

		::close(fd);

		auto rc = make_shared<Data>();

		rc->ptr = buffer;
		rc->dmi.length = datalength;

		return rc;
	}

 }
