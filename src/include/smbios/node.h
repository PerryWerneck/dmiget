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
  * @brief Declare SMBios node.
  */

 #pragma once

 #include <smbios/defs.h>
 #include <smbios/value.h>
 #include <iostream>
 #include <iterator>
 #include <memory>
 #include <functional>

 namespace SMBios {

	class SMBIOS_API Node {
	public:
		struct Info;

		struct Header{
			uint8_t type = 0;
			uint8_t length = 0;
			uint16_t handle = 0;
		};

		class Iterator {
		private:
			Node *node = nullptr;
			int offset = -1;

			void set(int offset);

		public:
			using iterator_category = std::forward_iterator_tag;
			using difference_type   = std::ptrdiff_t;
			using value_type        = Node;
			using pointer           = Node *;
			using reference         = Node &;

			constexpr Iterator() {
			}

			constexpr Iterator(Node *n) : node{n} {
			}

			Iterator(const Iterator &it);

			Iterator(const Iterator *it) : Iterator{*it} {
			}

			Iterator(std::shared_ptr<Data> data, int offset);
			~Iterator();

			reference operator*() const {
				return *node;
			}

			pointer operator->() {
				return node;
			}

			operator bool() const;

			Iterator operator++(int);

			bool operator==(const Iterator& rhs) const {
				return rhs.offset == offset;
			}

			bool operator!=(const Iterator& rhs) const {
				return rhs.offset != offset;
			}

			Iterator & operator++();

		};

		Node(const char *name, int index = 0);
		operator bool() const;

		/// @brief Get value by index.
		Value operator[](size_t index) const;

		const char *name() const noexcept;
		const char *description() const noexcept;

		bool multiple() const noexcept;

		static bool for_each(const std::function<bool(const Node &node)> &call);
		bool for_each(const std::function<bool(const Value &v)> &call) const;

		const Value::Info * values() const noexcept;

		std::shared_ptr<Value> find(const char *name) const;

		Value::Iterator begin() const;
		Value::Iterator end() const;

		Node & next(const char *name = "");

		Value::Iterator begin();
		Value::Iterator end();

		short type() const noexcept {
			return (short) header.type;
		}

		size_t size() const noexcept {
			return (size_t) header.length;
		}

		uint16_t handle() const noexcept {
			return header.handle;
		}

	private:

		/// @brief Construct an empty node.
		Node();

		std::shared_ptr<Data> data;
		int offset = -1;
		size_t index = 0;
		const Info *info;

		Header header;

		Node(std::shared_ptr<Data> d, const int offset);

	};

	SMBIOS_API Node::Iterator begin();
	SMBIOS_API Node::Iterator end();

 }

 namespace std {

	inline string to_string(const SMBios::Node &node) {
			return node.description();
	}

	inline ostream& operator<< (ostream& os, const SMBios::Node &node) {
			return os << node.description();
	}

	inline ostream& operator<< (ostream& os, const SMBios::Node *node) {
			return os << node->description();
	}

 }


