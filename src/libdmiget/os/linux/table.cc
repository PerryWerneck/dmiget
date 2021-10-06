/* SPDX-License-Identifier: LGPL-3.0-or-later */

/*
 * Copyright (C) 2021 Perry Werneck <perry.werneck@gmail.com>
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

 #include <dmiget/table.h>
 #include <internals.h>
 #include <cstring>
 #include <cerrno>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <unistd.h>
 #include <cstring>
 #include <iostream>

 using namespace std;

 namespace DMI {

	/// @brief File reader
	struct File {

		uint8_t * contents = nullptr;
		size_t length = 0;

		operator bool() const {
			return contents != nullptr;
		}

		inline size_t size() const noexcept {
			return length;
		}

		inline bool has_prefix(const char *prefix, size_t length) const noexcept {
			return contents && memcmp(contents,prefix,length) == 0;
		}

		File(const char *filename, size_t maxlen = 4096) {

			int fd = open(filename,O_RDONLY);
			if(fd < 0)
				return;

			struct stat statbuf;
			if (fstat(fd, &statbuf) == 0) {
                if(statbuf.st_size) {
					maxlen = statbuf.st_size;
                }
			}

			contents = new uint8_t[maxlen+1];
			memset(contents,0,maxlen+1);

			uint8_t * ptr = contents;
			length = 0;
			while(this->length < maxlen) {
				ssize_t bytes = read(fd,ptr,(maxlen - this->length));
				if(bytes < 0) {
					if(errno != EINTR) {
						cerr << filename << ": " << strerror(errno) << endl;
						delete[] contents;
						contents = nullptr;
						length = 0;
						break;
					}
				} else if(bytes == 0) {

					break;

				} else {
					ptr += bytes;
					length += bytes;
				}
			}

			::close(fd);

		}

		~File() {
			if(contents) {
				delete[] contents;
			}
		};

	};

	Table::Table() {

		File entry_point("/sys/firmware/dmi/tables/smbios_entry_point");
		File table("/sys/firmware/dmi/tables/DMI");

		if(entry_point && table) {

			// Got sysfs
			if(entry_point.size() >= 24 && entry_point.has_prefix("_SM3_", 5)) {
				smbios3_decode(entry_point.contents,table.contents);
			} else if(entry_point.size() >= 32 && entry_point.has_prefix("_SM_", 4)) {
//				smbios_decode(entry_point.contents,table.contents);
			} else if(entry_point.size() >= 31 && entry_point.has_prefix("_DMI_", 5)) {
//				legacy_decode(entry_point.contents,table.contents);
			}
		}

	}

	Table::~Table() {
	}

 }
