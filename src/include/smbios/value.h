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

		enum Type {
			Invalid,
			String,
			Integer
		};

		Value(const Value &src);

		Value(const Value *src);

		Value(std::shared_ptr<Data> data, size_t offset, const Value::Info *info, size_t item = 0);

		class Iterator {
		private:
			Value *value = nullptr;

		public:
			using iterator_category = std::forward_iterator_tag;
			using difference_type   = std::ptrdiff_t;
			using value_type        = Value;
			using pointer           = Value *;
			using reference         = Value &;

			Iterator(const Iterator &i) : Iterator{new Value{i.value}} {
			}

			Iterator(const Iterator *i) : Iterator{new Value{i->value}} {
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

		const char *name() const noexcept;
		const char *description() const noexcept;

		operator bool() const;

		std::string to_string() const;

		Value & next();

		/// @brief Find value using url formatter as DMI:///node/value
		static std::shared_ptr<Value> find(const char *url);

	protected:
		std::shared_ptr<Data> data;
		size_t offset;

		const Value::Info *info;
		size_t item;

	};

 };

 namespace std {

	inline string to_string(const SMBios::Value &value) {
			return value.to_string();
	}

	inline ostream& operator<< (ostream& os, const SMBios::Value &value) {
			return os << value.to_string();
	}

	inline ostream& operator<< (ostream& os, const SMBios::Value *value) {
			return os << value->to_string();
	}

 }
