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
  * @brief Implements node object.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <smbios/defs.h>
 #include <smbios/node.h>
 #include <smbios/value.h>
 #include <private/smbios.h>
 #include <private/constants.h>
 #include <stdexcept>
 #include <cstring>

 using namespace std;

 namespace SMBios {

	Node::Node() : Node{SMBios::Data::factory(),0} {
	}

	Node::Node(uint8_t type, int index) : Node{} {

		if(header.type != type) {
			next(type);
		}

		while(index-- > 0 && *this) {
			next(type);
		}

	}

	Node::Node(const char *name, int index) : Node{Node::Info::find(name)->id,index} {
	}

	Node Node::factory(const char *filename, const char *name, int index) {

		Node node{SMBios::Data::factory(filename),0};

		if(name && *name) {

			uint8_t type = Node::Info::find(name)->id;

			if(node.header.type != type) {
				node.next(type);
			}

			while(index-- > 0 && node) {
				node.next(type);
			}

		}

		return node;
	}


	/*

	Node::Node(const char *name, int index) : Node{SMBios::Data::factory(),0} {

		if(name && *name) {
			do {
				next(name);
			} while(*this && index-- > 0);
		}

	}

	Node::Node(const char *filename, const char *name, int index) :  {

		if(name && *name) {
			do {
				next(name);
			} while(*this && index-- > 0);
		}

	}

	*/

	Node::Node(std::shared_ptr<Data> d, const int o) : data{d}, offset{o}, info{Node::Info::find(*d->get(o))} {

		const uint8_t *ptr = data->get(o);

		header.type = ptr[0];
		header.length = ptr[1];
		header.handle = WORD(ptr+2);

	}

	Node::operator bool() const {
		return offset >= 0 && header.length >= 4 && header.type != 127;
	}

	Node & Node::operator=(const Node & src) {

		if(src.data) {
			data = src.data;
		} else {
			data = SMBios::Data::factory();
		}

		offset = src.offset;
		index = src.index;
		info = src.info;

		const uint8_t *ptr = data->get(offset);
		header.type = ptr[0];
		header.length = ptr[1];
		header.handle = WORD(ptr+2);

		return *this;
	}

	Node & Node::operator=(const uint8_t type) {

		rewind();
		if(header.type == type) {
			return *this;
		}

		return next(type);
	}

	Node & Node::operator=(const char *name) {
		return operator=(info->find(name)->id);
	}

	const char * Node::name() const noexcept {
		if(offset < 0) {
			return "";
		}
		return info->name;
	}

	const char * Node::description() const noexcept {
		if(offset < 0) {
			return "";
		}
		return info->description;
	}

	const Value::Info * Node::values() const noexcept {
		return info->values;
	}

	Value Node::operator[](size_t index) const {

		if(offset < 0) {
			throw logic_error("The selected node has no values");
		}

		size_t maxlen = info->size();
		if(index > maxlen) {
			index = maxlen;
		}

		return Value{data,(size_t) offset,info->values,index};
	}

	Value Node::operator[](const char *name) const {

		if(offset < 0) {
			throw runtime_error("Cant search on empty node");
		}

		Value value{data,(size_t) offset,info->values,0};

		if(!(name && *name)) {
			return value;
		}

		while(value) {
			if(!strcasecmp(name,value.name())) {
				return value;
			}
			value.next();
		}

		throw system_error(ENOENT,system_category(),name);

	}

	size_t Node::Info::size() const noexcept {
		size_t rc = 0;
		if(values) {
			while(values[rc].name && *values[rc].name) {
				rc++;
			}
		}
		return rc;
	}

	bool Node::multiple() const noexcept {
		if(offset > 0 && info) {
			return info->multiple;
		}
		return false;
	}

	Node & Node::rewind() {
		offset = 0;

		const uint8_t *ptr = data->get(offset);
		header.type = ptr[0];
		header.length = ptr[1];
		header.handle = WORD(ptr+2);

		if(header.length < 4 || header.type == 127) {
			offset = -1;
			return *this;
		}
		info = Node::Info::find(header.type);
		return *this;
	}

	Node & Node::next() {

		if(offset < 0) {
			return *this;
		}

		index++;
		if((data->count() && index >= data->count())) {
			offset = -1;
			return *this;
		}

		// Look for the next handle
		const uint8_t *buf = data->get(0);
		const uint8_t *next = buf+offset+header.length;

		while ((unsigned long)(next - buf + 1) < data->size() && (next[0] != 0 || next[1] != 0))
			next++;
		next += 2;

		offset = (next - buf);

		if( (offset+4) > ((int) data->size()) ) {
			offset = -1;
			return *this;
		}

		header.type = next[0];
		header.length = next[1];
		header.handle = WORD(next+2);

		if(header.length < 4 || header.type == 127) {
			offset = -1;
			return *this;
		}

		info = Node::Info::find(header.type);
		return *this;
	}

	Node & Node::next(uint8_t type) {

		next();
		while(header.type != type && *this) {
			next();
		}

		return *this;
	}

	Node & Node::next(const char *name) {
		if(name && *name) {
			return next(Info::find(name)->id);
		}
		return next();
	}

	std::shared_ptr<Value> Node::find(const char *name) const {

		if(offset < 0) {
			throw runtime_error("Cant search on empty node");
		}

		Value value{data,(size_t) offset,info->values,0};

		if(!(name && *name)) {
			return make_shared<Value>(value);
		}

		while(value) {
			if(!strcasecmp(name,value.name())) {
				return make_shared<Value>(value);
			}
			value.next();
		}

		throw system_error(ENOENT,system_category(),name);
	}

	Value::Iterator Node::begin() {
		if(offset < 0) {
			return end();
		}
		return Value::Iterator{new Value{data,(size_t) offset,info->values,0}};
	}

	Value::Iterator Node::end() {
		return Value::Iterator{new Value{data,(size_t) offset,info->values,info->size()}};
	}

 }
