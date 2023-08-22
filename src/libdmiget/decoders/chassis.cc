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

 #include <private/decoders.h>
 #include <private/decoders/tools.h>
 #include <private/decoders/chassis.h>
 #include <smbios/node.h>
 #include <iostream>
 #include <string>
 #include <cstring>

 using namespace std;

 namespace SMBios {

	std::string Decoder::ChassisState::as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const {

		static const char *state[] = {
			"Other", /* 0x01 */
			"Unknown",
			"Safe",
			"Warning",
			"Critical",
			"Non-recoverable" /* 0x06 */
		};

		auto code = as_uint(header,ptr,offset);

		if (code >= 0x01 && code <= 0x06)
			return state[code - 0x01];

		return "";
	}

	unsigned int Decoder::ChassisLock::as_uint(const Node::Header &header, const uint8_t *data, const size_t offset) const {
		if(offset > header.length) {
			return 0;
		}
		return (unsigned int) (data[offset] >> 7);
	}

	std::string Decoder::ChassisLock::as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const {

		static const char *state[] = {
			"Not Present",	// 0x00
			"Present",		// 0x01
		};

		if(offset > header.length) {
			return "";
		}

		auto code = as_uint(header,ptr,offset);

		if (code <= 0x01)
			return state[code];

		return "";

	}

 }

