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
  * @brief Inplements node iterator.
  */

 #include <config.h>
 #include <private/smbios.h>
 #include <smbios/defs.h>
 #include <smbios/node.h>
 #include <stdexcept>

 using namespace std;
// #include <private/node.h>

 namespace SMBios {

	struct Header {

		uint8_t type;
		uint8_t length;
		uint16_t handle;

		constexpr Header(const uint8_t *d) : type(d[0]), length(d[1]), handle(WORD(d+2)) {
		}

	};

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
		throw runtime_error("Incomplete");
	}

	Node::Iterator & Node::Iterator::operator++() {
		throw runtime_error("Incomplete");
	}

 }

