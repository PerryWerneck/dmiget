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
 #include <private/decoders/bios.h>
 #include <smbios/node.h>
 #include <iostream>
 #include <string>
 #include <cstring>

 using namespace std;

 namespace SMBios {

	std::string Decoder::FirmwareRevision::as_string(const Node::Header &, const uint8_t *ptr, const size_t offset) const {

		ptr += offset;

		if(ptr[0] == 0xFF || ptr[1] == 0xFF) {
			return "";
		}

		string rc{std::to_string((unsigned int) ptr[0])};
		rc += ".";
		rc += std::to_string((unsigned int) ptr[1]);

		return rc;
	}


 }

