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
 #include <private/decoders/processor.h>
 #include <smbios/node.h>
 #include <iostream>
 #include <string>
 #include <cstring>
 #include <sstream>
 #include <iomanip>

 using namespace std;

 namespace SMBios {

	unsigned int Decoder::ProcessorType::as_uint(const Node::Header &, const uint8_t *ptr, const size_t offset) const {
		return (unsigned int) ptr[offset];
	}

	std::string Decoder::ProcessorType::as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const {

		unsigned int code{this->as_uint(header,ptr,offset)};

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

	std::string Decoder::ProcessorFrequency::as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const {

		uint16_t code = as_uint(header,ptr,offset);

		if(!code) {
			return "";
		}

		string response = std::to_string(code);

		return response + " MHz";

	}

	unsigned int Decoder::ProcessorVoltage::as_uint(const Node::Header &, const uint8_t *ptr, const size_t offset) const {

		unsigned int code = ptr[offset];

		if (code & 0x80) {
			return code & 0x7f;
		} else if ((code & 0x07) == 0x00) {
			return 0;
		}

		static unsigned int voltage[] = {
			50, // 5.0
			33, // 3.3
			29  // 2.9
		};

		for (int i = 0; i <= 2; i++) {
			if (code & (1 << i)) {
				return voltage[i];
			}
		}

		return 0;

	}

	std::string Decoder::ProcessorVoltage::as_string(const Node::Header &, const uint8_t *ptr, const size_t offset) const {

		static const char *voltage[] = {
			"5.0 V", // 0
			"3.3 V",
			"2.9 V" // 2
		};

		stringstream stream;

		unsigned int code = ptr[offset];

		if (code & 0x80) {

			stream << fixed << setprecision(1) << ((float)(code & 0x7f) / 10) << " V";

		} else if ((code & 0x07) == 0x00) {

			stream << "Unknown";

		} else {

			bool spc = false;
			for (int i = 0; i <= 2; i++) {
				if (code & (1 << i)) {
					if(spc) {
						stream << " ";
					}
					stream << voltage[i];
					spc = true;
				}
			}

		}

		return stream.str();

	}

 }

