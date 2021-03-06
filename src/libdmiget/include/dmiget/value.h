/* SPDX-License-Identifier: LGPL-3.0-or-later */

/*
 * Copyright (C) 2021 Perry Werneck <perry.werneck@gmail.com>
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

 #pragma once

 #include <dmiget/defs.h>
 #include <string>
 #include <stdint.h>
 #include <functional>
 #include <memory>

 namespace DMIget {

	struct Header;

	class DMIGET_API Value {
	public:

		struct Record;
		struct Type;

	protected:

		struct {
			std::string name;
			std::string description;
		} info;

		const uint8_t typeindex = 1;
		const Type * type = nullptr;

	public:
		Value() { }

		Value(const Type *type, const Record *record, const uint8_t typeindex = 1);
		virtual ~Value();

		std::string url() const;

		inline const char * name() const {
			return info.name.c_str();
		}

		const char * description() const {
			return info.name.c_str();
		}

		virtual std::string as_string() const;
		virtual unsigned int as_uint() const;

	};

 }

 namespace std {

	inline string to_string(const ::DMIget::Value &value) {
		return value.as_string();
	}

	inline ostream& operator<< (ostream& os, const ::DMIget::Value &value) {
		return os << value.as_string();
	}

	inline ostream& operator<< (ostream& os, const ::DMIget::Value *value) {
		return os << value->as_string();
	}

 }
