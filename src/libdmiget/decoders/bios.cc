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
 #include <sstream>
 #include <iomanip>

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

	unsigned int Decoder::BiosAddress::as_uint(const Node::Header &, const uint8_t *data, const size_t) const {

		if(WORD(data + 0x06) == 0) {
			return 0;
		}

		return WORD(data + 0x06);
	}


	std::string Decoder::BiosAddress::as_string(const Node::Header &header, const uint8_t *data, const size_t offset) const {

		if(WORD(data + 0x06) == 0) {
			return "";
		}

		stringstream stream;
		stream << "0x" << uppercase << hex << as_uint(header,data,offset) << "0" << dec;

		return stream.str();

	}

	uint64_t Decoder::BiosRuntimeSize::as_uint64(const Node::Header &, const uint8_t *data, const size_t) const {

		if(WORD(data + 0x06) == 0) {
			return 0;
		}

		uint32_t code = ((0x10000 - WORD(data + 0x06)) << 4);

		if (code & 0x000003FF) {
			return code;
		}

		code >>= 10;

		return ((uint64_t) code ) * ((uint64_t) 1024);

	}

	uint64_t Decoder::BiosRomSize::as_uint64(const Node::Header &header, const uint8_t *data, const size_t) const {

		if (data[0x09] != 0xFF) {
			u64 s;
			s.l = (data[0x09] + 1) << 6;
			return s.as_memory_size_bytes();
		}

		uint16_t code2 = (header.length < 0x1A ? 16 : WORD(data + 0x18));

		switch(code2 >> 14) {
		case 0:
			return ((uint64_t) code2 & 0x3FFF) * 1048576LL;

		case 1:
			return ((uint64_t) code2 & 0x3FFF) * 1073741824LL;
		default:
			return 0;
		}

	}

 }

