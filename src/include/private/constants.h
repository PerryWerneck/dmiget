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
  * @brief Declare constants.
  */

 #pragma once

 #include <smbios/defs.h>
 #include <private/smbios.h>
 #include <smbios/value.h>
 #include <smbios/node.h>

 namespace SMBios {

	struct Node::Info {
		uint8_t id = 0;
		bool multiple = false;
		const char *name = nullptr;
		const char *description = nullptr;
		const Value::Info * values = nullptr;

		static const Info & find(uint8_t id);
	};

	struct Value::Info {

		const char *name = nullptr;
		Value * (*factory)(const Value::Info &info, const uint8_t *ptr);
		uint8_t offset = 0xFF;
		const char *description = nullptr;

	};

 }

