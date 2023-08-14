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
  * @brief Implements node iterator.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <private/smbios.h>
 #include <smbios/defs.h>
 #include <smbios/node.h>
 #include <stdexcept>
 #include <private/smbios.h>
 #include <private/constants.h>
 #include <cstring>

 using namespace std;

 namespace SMBios {

	struct Header {

		uint8_t type;
		uint8_t length;
		uint16_t handle;

		constexpr Header(const uint8_t *d) : type(d[0]), length(d[1]), handle(WORD(d+2)) {
		}

	};

	Node::Iterator::Iterator(const Node::Iterator &it) : node{new Node{*it.node}}, offset{it.offset} {
	}

	Node::Iterator::Iterator(std::shared_ptr<Data> data, int o) : offset{o} {
		// Create node.
		node = new Node{data,offset};
	}

	Node::Iterator::~Iterator() {
		delete node;
	}

	Node::Iterator begin() {
		return Node::Iterator{Data::factory(),0};
	}

	Node::Iterator end() {
		return Node::Iterator{};
	}

	Node::Iterator::operator bool() const {
		return offset >= 0 && node->header.length >= 4 && node->header.type != 127;
	}

	Node::Iterator Node::Iterator::operator++(int) {
		Iterator tmp{*this};
		operator++();
		return tmp;
	}

	Node::Iterator & Node::Iterator::operator++() {
		node->next();
		return *this;
	}

	bool Node::for_each(const std::function<bool(const Node &n, const size_t index, const Value &v)> &call) {

		char indexes[0xff];
		memset(indexes,0,sizeof(indexes));

		for(Node node{""};node;node.next("")) {

			Value value{node.data,(size_t) node.offset,node.info->values,0};

			size_t index = 0;
			if(node.multiple()) {
				index = ++indexes[node.info->id];
			}

			while(value) {
				if(call(node,index,value)) {
					return true;
				}
				value.next();
			}

		}

		return false;

	}

	bool Node::for_each(uint8_t type, const std::function<bool(const Node &node)> &call) {

		for(Node node{""};node;node.next("")) {

			if(node.type() == type && call(node)) {
				return true;
			}

		}

		return false;

	}

	bool Node::for_each(const std::function<bool(const Node &node)> &call) {

		for(Node node{""};node;node.next("")) {
			if(call(node)) {
				return true;
			}
		}
		return false;

	}

	bool Node::for_each(const std::function<bool(std::shared_ptr<Value> v)> &call) const {

		if(offset < 0 || !(info && info->values)) {
			return false;
		}

		class InternalValue : public Value {
		public:
			InternalValue(std::shared_ptr<Data> data, size_t offset, const Value::Info *info) : Value(data,offset,info,0) {
			}

			bool set(size_t item) {
				this->item = item;
				return info[item].name;
			}

		};

		auto value = make_shared<InternalValue>(data,offset,info->values);

		for(size_t item = 0; value->set(item);item++) {
			if(call(value)) {
				return true;
			}
		}

		/*
		Value value{data,(size_t) offset,info->values,0};
		while(value) {
			if(call(make_shared<Value>(value))) {
				return true;
			}
			value.next();
		}
		*/

		return false;
	}

	bool Node::for_each(const std::function<bool(const Value &v)> &call) const {

		if(offset < 0) {
			return false;
		}

		Value value{data,(size_t) offset,info->values,0};

		while(value) {
			if(call(value)) {
				return true;
			}
			value.next();
		}

		return false;
	}

 }

