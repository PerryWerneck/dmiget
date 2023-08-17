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
  * @brief Implements processor type decoders.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 /*
 #include <private/decoders.h>
 #include <smbios/node.h>
 #include <iostream>
 #include <string>
 #include <cstring>

 using namespace std;

 namespace SMBios {

	unsigned int Decoder::ProcessorType::as_uint(const uint8_t *ptr, const size_t offset) const {
		return (unsigned int) ptr[offset];
	}

	std::string Decoder::ProcessorType::as_string(const uint8_t *ptr, const size_t offset) const {

		unsigned int code{this->as_uint(ptr,offset)};

		static const char *type[] = {
			"Other", // 0x01
			"Unknown",
			"Central Processor",
			"Math Processor",
			"DSP Processor",
			"Video Processor" // 0x06
		};

		if (code >= 0x01 && code <= 0x06)
			return type[code - 0x01];

		return "Unknown";

	}

 }
 */
