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
  * @brief Declare SMBios value.
  */

 #pragma once

 #include <smbios/defs.h>
 #include <iostream>
 #include <iterator>
 #include <memory>

 namespace SMBios {

	class SMBIOS_API Value {
	public:
		struct Info;

		class Iterator {
		private:
			Value *value = nullptr;

		public:
			using iterator_category = std::forward_iterator_tag;
			using difference_type   = std::ptrdiff_t;
			using value_type        = Value;
			using pointer           = Value *;
			using reference         = Value &;

			constexpr Iterator() {
			}

			constexpr Iterator(Value *v) : value{v} {
			}

			~Iterator();

			reference operator*() const {
				return *value;
			}

			pointer operator->() {
				return value;
			}

			operator bool() const;

			Iterator operator++(int);

			bool operator==(const Iterator& rhs) const;

			bool operator!=(const Iterator& rhs) const;

			Iterator & operator++();

		};

		Value(const Node &node, const char *name);
		~Value();

		const char *name() const noexcept;
		const char *description() const noexcept;

	protected:
		std::shared_ptr<Data> data;
		const Info &info;

	};

 }
