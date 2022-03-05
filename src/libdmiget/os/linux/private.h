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

 #include <config.h>
 #include <dmiget/defs.h>
 #include <dmiget/value.h>
 #include <stdexcept>
 #include <string>
 #include <iostream>

 using namespace std;

 namespace DMIget {


 }

 /*
 namespace DMIget {

 	class Entry {
	public:
		uint8_t index;
		const char *name = nullptr;
		const char *description = nullptr;
		//const Entry *children = nullptr;

		inline const char * getName() const noexcept {
			return this->name ? this->name : this->description;
		}

	};

	class Type {
	public:
		uint8_t id;
		uint8_t entry;
		const char *name = nullptr;
		const char *description = nullptr;
		const Entry *children = nullptr;

		static const Type * find(const string &name);
		const Entry * getChild(const char *name) const;

		inline const char * getName() const noexcept {
			return this->name ? this->name : this->description;
		}

	};


	#define ENTRY_LIST_TERMINATOR { 0xFF, nullptr, nullptr }

	class Value::Reader {
	private:
		const Type *type;
		const Entry *entry;

		size_t read(const char *name, char buffer[4096]) const;

	public:
		Reader(const Type *type, const Entry *entry);
		~Reader();

		const char * name() const;
		const char * description() const;
		const std::string as_string() const;

	};

 }
 */
