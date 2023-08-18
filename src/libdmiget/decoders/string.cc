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
  * @brief Implements string decoder.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <string>
 #include <private/decoders.h>

 using namespace std;

 namespace SMBios {


	/*
	string Decoder::String::as_string(const Node::Header &header, const uint8_t *ptr) const {

		if(offset > header.length) {
			return "";
		}

		uint8_t index = ptr[offset];
		if (index == 0)
			return "";

		ptr += header.length;

		while (index > 1 && *ptr) {
			ptr += strlen((const char *) ptr);
			ptr++;
			index--;
		}

		return string{(const char *) ptr};

	}
	*/

 }

 /*
 #include <private/constants.h>
 #include <private/decoders.h>
 #include <smbios/node.h>
 #include <iostream>
 #include <string>
 #include <cstring>

 using namespace std;

 namespace SMBios {

	string Decoder::StringIndex::as_string(const uint8_t *ptr, size_t index) const {

		Node::Header *header{(Node::Header *) ptr};

		ptr += header->length;
		while (index > 1 && *ptr) {
			ptr += strlen((const char *) ptr);
			ptr++;
			index--;
		}

		return string{(const char *) ptr};
	}

	string Decoder::String::as_string(const uint8_t *ptr, size_t offset) const {

		Node::Header *header{(Node::Header *) ptr};

		uint8_t index = ptr[offset];
		if (index == 0)
			return "";

		ptr += header->length;

		while (index > 1 && *ptr) {
			ptr += strlen((const char *) ptr);
			ptr++;
			index--;
		}

		return string{(const char *) ptr};

	}

	string Decoder::MemoryDeviceFormFactor::as_string(const uint8_t *ptr, const size_t offset) const {

		static const char *form_factor[] = {
			"Other", // 0x01
			"Unknown",
			"SIMM",
			"SIP",
			"Chip",
			"DIP",
			"ZIP",
			"Proprietary Card",
			"DIMM",
			"TSOP",
			"Row Of Chips",
			"RIMM",
			"SODIMM",
			"SRIMM",
			"FB-DIMM",
			"Die" // 0x10
		};

		uint8_t code = ptr[offset];

		if (code >= 0x01 && code <= 0x10)
			return form_factor[code - 0x01];

		return "";

	}

	uint64_t Decoder::MemorySize::as_uint64(const uint8_t *ptr, const size_t) const {

		Node::Header *header{(Node::Header *) ptr};

		if(header->length >= 0x20 && *((uint16_t *) (ptr+0x0C)) == 0x7FFF) {

			// Extended size
			uint32_t code = *((uint32_t *) (ptr+0x1c)) & 0x7FFFFFFFUL;

			if (code & 0x3FFUL)
				return ((uint64_t) code) * 1048576LL; // MB
			else if (code & 0xFFC00UL)
				return ((uint64_t) (code >> 10)) * 1073741824LL; // GB
			else
				return ((uint64_t) (code >> 20)) * 1099511627776LL; // TB

		} else {

			// Device size
			uint16_t code = *((uint16_t *) (ptr+0x0c));

			if(code == 0 || code == 0xFFFF) {
				return 0;
			}

			u64 s;
			s.l = (code & 0x7FFF);
			if(!(code & 0x8000))
				s.l <<= 10;

			return s.as_memory_size_bytes(1);

		}

	}

	std::string Decoder::MemorySize::as_string(const uint8_t *ptr, const size_t) const {

		Node::Header *header{(Node::Header *) ptr};

		if(header->length >= 0x20 && *((uint16_t *) (ptr+0x0C)) == 0x7FFF) {

			// Extended size
			uint32_t code = *((uint32_t *) (ptr+0x1c)) & 0x7FFFFFFFUL;

			if (code & 0x3FFUL)
				return string{"Size "} + std::to_string((unsigned long) code) + "MB";
			else if (code & 0xFFC00UL)
				return string{"Size "} + std::to_string((unsigned long) (code >> 10)) + " GB";
			else
				return string{"Size "} + std::to_string((unsigned long) (code >> 20)) + " TB";

		} else {

			// Device size
			uint16_t code = *((uint16_t *) (ptr+0x0c));

			if(code == 0 || code == 0xFFFF) {
				return "";
			}

			u64 s;
			s.l = (code & 0x7FFF);
			if(!(code & 0x8000))
				s.l <<= 10;

			return s.as_memory_size_string(1);

		}
	}

 }
 */
