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

		enum Format : uint8_t {
			Invalid,
			SmBios3,
			SmBios,
			Legacy
		} format = Invalid;

		struct {
			uint64_t base = 0;
			uint32_t len = 0;
			uint16_t num = 0;
			uint32_t version = 0;
			uint8_t *contents = nullptr;
		} dmi;

		/// @brief Identify SMBIOS format.
		bool identify(const uint8_t *entry);

		/// @brief Set DMI table contents.
		bool set(const uint8_t *dmi, size_t length);

	public:
		Table();
		~Table();

		inline operator bool() const noexcept {
			return dmi.contents != nullptr;
		}

	};

 }
