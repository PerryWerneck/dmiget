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
 #include <stdint.h>
 #include <stddef.h>

 namespace DMI {

	class DMIGET_API Table {
	private:

		size_t length = 0;
		uint8_t * contents = nullptr;

		enum Format : uint8_t {
			Invalid,
			SmBios3,
			SmBios,
			Legacy
		} format = Invalid;

		void set(const Format format, uint8_t *contents, size_t length);

	public:
		Table();
		~Table();

		inline operator bool() const noexcept {
			return contents != nullptr;
		}

	};

 }
