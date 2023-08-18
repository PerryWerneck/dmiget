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
  * @brief Implements probe decoder.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <private/decoders/probe.h>
 #include <string>
 #include <sstream>
 #include <iomanip>

 using namespace std;

 namespace SMBios {

	std::string Decoder::TemperatureProbeValue::as_string(const Node::Header &, const uint8_t *ptr, const size_t offset) const {

		uint16_t code = WORD(ptr+offset);

		if (code == 0x8000)
			return "";

		std::stringstream stream;

		stream << fixed << setprecision(1) << ( ((float) code) / 10) << " ºC";

		return stream.str();
	}

	uint64_t Decoder::TemperatureProbeValue::as_uint64(const Node::Header &, const uint8_t *ptr, const size_t offset) const {

		uint16_t code = WORD(ptr+offset);

		if(code == 0x8000) {
			return 0;
		}

		return code;

	}

 }
