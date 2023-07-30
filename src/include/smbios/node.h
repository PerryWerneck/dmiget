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

		class Iterator {
		private:
			Node *node = nullptr;

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

			~Iterator();

			reference operator*() const {
				return *node;
			}

			pointer operator->() {
				return node;
			}

			operator bool() const;

			Iterator operator++(int);

			bool operator==(const Iterator& rhs) const;

			bool operator!=(const Iterator& rhs) const;

			Iterator & operator++();

		};

		Node(const char *name);
		~Node();

		const char *name() const noexcept;
		const char *description() const noexcept;

		static bool for_each(const std::function<bool(const Node &node)> &call);
		bool for_each(const std::function<bool(const Value &v)> &call) const;

		Value::Iterator begin() const;
		Value::Iterator end() const;

	private:
		std::shared_ptr<Data> data;
		const Info &info;

	};

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


