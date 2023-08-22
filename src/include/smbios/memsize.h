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
  * @brief Declare Memory size object.
  */

 #pragma once

 #include <smbios/defs.h>
 #include <smbios/value.h>
 #include <iostream>
 #include <cstdint>

 namespace SMBios {

	class SMBIOS_API MemSize : public Value {
	private:
		uint64_t value;

	public:
		MemSize();

		std::string as_string(int precision) const;
		std::string as_string() const override;

		bool empty() const override;
		const char *name() const noexcept override;
		const char *description() const noexcept override;

		inline uint64_t as_uint64() const override {
			return value;
		}

	};

 };

