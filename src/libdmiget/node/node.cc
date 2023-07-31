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

 #include <config.h>
 #include <smbios/defs.h>
 #include <smbios/node.h>
 #include <smbios/value.h>
 #include <private/smbios.h>
 #include <private/constants.h>
 #include <stdexcept>
 #include <cstring>

 using namespace std;

 namespace SMBios {

	Node::Node() : info{Node::Info::find(0)} {
	}

	Node::Node(const char *name, int index) : Node{SMBios::Data::factory(),0} {

		if(name && *name) {
			do {
				next(name);
			} while(index-- > 0);
		}

	}

	Node::Node(std::shared_ptr<Data> d, const int o) : data{d}, offset{o}, info{Node::Info::find(*d->get(o))} {

		const uint8_t *ptr = data->get(o);

		header.type = ptr[0];
		header.length = ptr[1];
		header.handle = WORD(ptr+2);

	}

	Node::operator bool() const {
		return offset >= 0 && header.length >= 4 && header.type != 127;
	}

	const char * Node::name() const noexcept {
		return info->name;
	}

	const char * Node::description() const noexcept {
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

		return Value{data,(size_t) offset,*this,index};
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

	Node & Node::next(const char *name) {

		if(offset < 0) {
			return *this;
		}

		// Get next node.
		do {
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

			info = Node::Info::find(*data->get(offset));

		} while(name && *name && strcasecmp(name,info->name));

		return *this;

	}

	Value::Iterator Node::begin() {
		if(offset < 0) {
			return end();
		}

		return Value::Iterator{new Value{data,(size_t) offset,*this,0}};

	}

	Value::Iterator Node::end() {
		return Value::Iterator{(Value *) nullptr};
	}

 }
