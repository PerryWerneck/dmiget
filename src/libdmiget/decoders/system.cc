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
  * @brief Brief description of this source.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <private/decoders.h>
 #include <private/decoders/system.h>
 #include <smbios/node.h>
 #include <iostream>
 #include <string>
 #include <cstring>

 using namespace std;

 namespace SMBios {

	std::string Decoder::SystemWakeUpType::as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const {

		static const char *type[] = {
			"Reserved", // 0x00
			"Other",
			"Unknown",
			"APM Timer",
			"Modem Ring",
			"LAN Remote",
			"Power Switch",
			"PCI PME#",
			"AC Power Restored" // 0x08
		};

		uint8_t code = as_uint(header,ptr,offset);
		if (code <= 0x08)
			return type[code];

		return std::to_string(code);

	}

 }

