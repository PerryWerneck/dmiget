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

	Value::Value(const char *path) {

		/*
		const char *ptr;

		if(strncasecmp(path,"dmi://",6)) {
			throw runtime_error("Invalid scheme; the DMI URL should start with dmi://");
		}

		path += 6;

		// Get type.
		ptr = strchr(path,'/');
		if(!ptr) {
			throw runtime_error("Invalid URL");
		}

		const Type * type = Type::find(string(path,ptr-path));

		// Get node
		path = ptr+1;

		const Entry *node = nullptr;

		ptr = strchr(path,'/');
		if(ptr) {
			node = type->getChild(string(path,ptr-path).c_str());
		} else {
			node = type->getChild(path);
		}

		this->reader = new Value::Reader(type,node);
		*/

	}

	Value::~Value() {
		delete this->reader;
	}

	const char * Value::name() const {
//		return reader->name();
	}

	const char * Value::description() const {
//		return reader->description();
	}

	const std::string Value::as_string() const {
//		return reader->as_string();
	}

 }
