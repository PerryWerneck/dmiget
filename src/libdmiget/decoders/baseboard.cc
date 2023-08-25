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
  * @brief Implement integer decoders.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <string>
 #include <private/decoders.h>
 #include <private/decoders/tools.h>
 #include <private/decoders/baseboard.h>

 using namespace std;

 namespace SMBios {

	std::string Decoder::BaseBoardType::as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const {

		static const char *type[] = {
			"Unknown", // 0x01
			"Other",
			"Server Blade",
			"Connectivity Switch",
			"System Management Module",
			"Processor Module",
			"I/O Module",
			"Memory Module",
			"Daughter Board",
			"Motherboard",
			"Processor+Memory Module",
			"Processor+I/O Module",
			"Interconnect Board" // 0x0D
		};

		auto code = as_uint(header,ptr,offset);

		if (code >= 0x01 && code <= 0x0D)
			return type[code - 0x01];

		return std::to_string(code);

	}


 }

