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

	Value * Value::create(const char *path) {

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

		const Node *node = nullptr;

		ptr = strchr(path,'/');
		if(ptr) {
			node = type->getChild(string(path,ptr-path).c_str());
		} else {
			node = type->getChild(path);
		}

		return new Linux::Value(type,node);

	}


	Linux::Value::Value(const Type *t, const Node *n) : type(t), node(n) {
	}

	Linux::Value::~Value() {
	}

	const char * Linux::Value::name() const {
		return node->name ? node->name : "";
	}

	const char * Linux::Value::description() const {
		return node->description ? node->description : "";
	}

	size_t Linux::Value::read(const char *name, char buffer[4096]) const {

		string filename{"/sys/firmware/dmi/"};
		filename += to_string(type->id);
		filename += '-';
		filename += to_string(node->id);
		filename += '/';
		filename += name;

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

	const std::string Linux::Value::as_string() const {

		char buffer[4096];
		size_t offset = 0;

		// Get header length
		read("length",buffer);
		offset = atoi(buffer);


		return "NOT IMPLEMENTED";
	}

 }
