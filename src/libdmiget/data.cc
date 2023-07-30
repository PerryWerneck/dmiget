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
  * @brief Common methods to smbios data class
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

 using namespace std;

 namespace SMBios {

	std::shared_ptr<Data> Data::factory() {
		return make_shared<Data>();
	}

	std::shared_ptr<Data> factory(const char *filename) {

		throw std::system_error(ENOTSUP,std::system_category(),filename);

		/*
		int fd = open(filename,O_RDONLY);

		if(fd < 0) {
			throw std::system_error(errno,std::system_category(),filename);
		}

		struct stat statbuf;
		if (fstat(fd, &statbuf) != 0) {
			int err = errno;
			::close(fd);
			throw std::system_error(err,std::system_category(),filename);
		}

		uint8_t *buffer = new uint8_t[statbuf.st_size+1];
		memset(buffer,0,statbuf.st_size+1);

		uint8_t *ptr = buffer;

		size_t pos = 0;
		while(pos < statbuf.st_size) {

			ssize_t bytes = read(fd,ptr,(pos - statbuf.st_size));

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

		return make_shared<Data>(buffer,statbuf.st_size);
		*/

	}

	Data::Data(uint8_t *p, int l) : ptr{p}, length{l} {
	}

	Data::~Data() {
		delete[] ptr;
	}

 }


