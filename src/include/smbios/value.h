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
 #include <cstring>

 namespace SMBios {

	/// @brief SMBios value.
	class SMBIOS_API Value {
	public:

		/// @brief Iterator for node contents.
		class SMBIOS_API Iterator {
		private:
			std::shared_ptr<Value> value;

		public:

			Iterator() {
			}

			Iterator(std::shared_ptr<Value> v) : value{v} {
			}

			Iterator(const Iterator &it) : Iterator{it.value} {
			}

			Iterator(const Iterator *it) : Iterator{it->value} {
			}

			inline Iterator & operator=(std::shared_ptr<Value> v) {
				value = v;
				return *this;
			}

			inline Iterator & operator=(const Iterator &it) {
				value = it.value;
				return *this;
			}

			inline Iterator & operator=(const Iterator *it) {
				value = it->value;
				return *this;
			}

			using iterator_category = std::forward_iterator_tag;

			~Iterator();

			/// @brief Create a new value for current item.
			std::shared_ptr<Value> operator*() const {
				return value;
			}

			std::shared_ptr<Value> operator->() {
				return value;
			}

			operator bool() const;

			Iterator operator++(int);

			virtual bool operator==(const Iterator& rhs) const;

			bool operator!=(const Iterator& rhs) const {
				return !operator==(rhs);
			}

			Iterator & operator++();

		};

		/// @brief Find value using url formatter as DMI:///node/value
		static std::shared_ptr<Value> find(const char *url);

		// Pure abstract object, cant copy it.
		Value(const Value &src) = delete;
		Value(const Value *src) = delete;

		bool operator==(const Value &src) const noexcept;

		bool operator==(const char *name) const noexcept;

		/// @brief Get value name.
		virtual const char *name() const noexcept = 0;

		/// @brief Get value description.
		virtual const char *description() const noexcept = 0;

		/// @brief Get value as string.
		virtual std::string as_string() const = 0;

		/// @brief Does the value has contents?
		virtual bool empty() const = 0;

		/// @brief Get value as an uint64.
		virtual uint64_t as_uint64() const;

		/// @brief Get value as an unsigned int.
		virtual unsigned int as_uint() const;

		/// @brief Skip to next value.
		virtual Value & next();

		/// @brief Create a copy of the object as shared_ptr
		virtual std::shared_ptr<Value> clone() const;

		virtual operator bool() const {
			return !empty();
		}

		inline operator uint64_t() const {
			return as_uint64();
		}

		inline operator unsigned int() const {
			return as_uint();
		}

		inline operator std::string() const {
			return as_string();
		}


#ifndef _MSC_VER
		inline std::string to_string() const {
			return as_string();
		}
#endif /// !_MSC_VER

	protected:
		int offset = -1;
		size_t item = (size_t) -1;

		constexpr Value() = default;

		constexpr Value(int o, size_t i) : offset{o}, item{i} {
		}

	};

 };

 namespace std {

	inline string to_string(const SMBios::Value &value) {
		return value.as_string();
	}

	inline ostream& operator<< (ostream& os, const SMBios::Value &value) {
			return os << value.as_string();
	}

	inline ostream& operator<< (ostream& os, const SMBios::Value *value) {
			return os << value->as_string();
	}

	inline ostream& operator<< (ostream& os, const shared_ptr<SMBios::Value> value) {
			return os << value->as_string();
	}
 }
