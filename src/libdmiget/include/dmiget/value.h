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

 namespace DMI {

	class DMIGET_API Value {
	public:

		enum ContentType : uint8_t {
			Invalid,
			String
		};

		struct Record {

			const char *name = nullptr;

			ContentType type = Invalid;

			uint8_t offset = 0xFF;

			const char *description = nullptr;

		};

		struct Type {
			uint8_t id = 0;
			bool multiple = false;
			const char *name = nullptr;
			const char *description = nullptr;
			const Record * records = nullptr;

			static const Type * find(uint8_t id);
		};

	protected:

		const uint8_t typeindex = 1;
		const Type * type = nullptr;
		const Record * record = nullptr;

	public:
		constexpr Value() { }
		constexpr Value(const Type *t, const Record *r, const uint8_t i = 1) : typeindex(i), type(t), record(r) { }

		virtual ~Value();

		std::string url() const;

		const char * name() const;
		const char * description() const;
		virtual std::string as_string() const;

	};

 }

 namespace std {

	inline string to_string(const DMI::Value &value) {
		return value.as_string();
	}

	inline ostream& operator<< (ostream& os, const DMI::Value &value) {
		return os << value.as_string();
	}

 }
