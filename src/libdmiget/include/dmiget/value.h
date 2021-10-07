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

 #include <dmiget/defs.h>
 #include <string>
 #include <stdint.h>

 namespace DMI {

	class DMIGET_API Value {
	public:

		struct Record {

			const char *name = nullptr;

			enum Type : uint8_t {
				Invalid,
				String
			} type = Invalid;

			uint8_t offset = 0xFF;

			const char *description = nullptr;

		};

		struct Type {
			uint8_t id = 0;
			const char *name = nullptr;
			const char *description = nullptr;
			const Record * records = nullptr;

			static const Type * find(uint8_t id);
		};

	private:

		const Type * type = nullptr;
		const Record * record = nullptr;

	public:
		constexpr Value() { }
		virtual ~Value();

		const char * name() const;
		const char * description() const;
		virtual const std::string as_string() const;

	};



 }

