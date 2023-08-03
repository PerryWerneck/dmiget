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

	bool Node::for_each(const std::function<bool(const Node &node)> &call) {

		for(Node node{""};node;node.next("")) {
			if(call(node)) {
				return true;
			}
		}
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

