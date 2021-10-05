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

 #include "private.h"
 #include <cstring>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <unistd.h>

 namespace DMI {

	Value::Reader::Reader(const Type *t, const Entry *e) : type(t), entry(e) {
	}

	Value::Reader::~Reader() {
	}

	const char * Value::Reader::name() const {
		return entry->name ? entry->name : "";
	}

	const char * Value::Reader::description() const {
		return entry->description ? entry->description : "";
	}

	size_t Value::Reader::read(const char *name, char buffer[4096]) const {

		string filename{"/sys/firmware/dmi/entries/"};
		filename += to_string(type->id);
		filename += '-';
		filename += to_string(type->entry);
		filename += '/';
		filename += name;

#ifdef DEBUG
		cout << "Reading " << filename << endl;
#endif // DEBUG

		int fd = open(filename.c_str(),O_RDONLY);
		if(fd < 0) {
			string msg{"Error opening "};
			msg += filename;
			throw system_error(errno,system_category(),msg);
		}

		memset(buffer,0,4096);
		auto length = ::read(fd,buffer,4095);
		if(length < 0) {
			string msg{"Error reading "};
			msg += filename;
			auto err = errno;
			close(fd);
			throw system_error(err,system_category(),msg);
		}

		close(fd);

		return (size_t) length;

	}

	const std::string Value::Reader::as_string() const {

		char buffer[4096];
		size_t offset = 0;

		// Get header length.
		read("length",buffer);
		offset = atoi(buffer);

		// Get DMI data.
		read("raw",buffer);
		const char *text = &buffer[offset];

		size_t ix = (size_t) this->entry->index;
		while(ix-- > 0) {

			if(!*text) {
				throw runtime_error(string{"Can't get string response for dmi://"} + type->getName() + "/" + entry->getName());
			}

			text += strlen(text)+1;

		}

		return text;

	}

 }
