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
  * @brief Declare abstract decoder.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <smbios/defs.h>
 #include <private/data.h>
 #include <smbios/value.h>
 #include <private/decoders.h>

 namespace SMBios {


 }

 /*
 #include <private/constants.h>
 #include <ctype.h>
 #include <stdexcept>

 using namespace std;

 namespace SMBios {

	std::string Decoder::Abstract::as_string(const uint8_t *, size_t) const {
		return "";
	}

	unsigned int Decoder::Abstract::as_uint(const uint8_t *ptr, size_t offset) const {

		unsigned int value = 0;
		std::string str{as_string(ptr,offset)};

		for(const char *p = str.c_str();*p && isdigit(*p);p++) {
			value *= 10;
			value += ('0' - *p);
		}

		return value;

	}

	uint64_t Decoder::Abstract::as_uint64(const uint8_t *ptr, const size_t offset) const {

		uint64_t value = 0;
		std::string str{as_string(ptr,offset)};

		for(const char *p = str.c_str();*p && isdigit(*p);p++) {
			value *= 10;
			value += ('0' - *p);
		}

		return value;

	}

 }
 */
