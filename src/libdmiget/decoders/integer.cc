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
 #include <smbios/node.h>
 #include <iostream>
 #include <string>
 #include <cstring>
 #include <sstream>
 #include <iomanip>

 using namespace std;

 namespace SMBios {

	unsigned int Decoder::UInt16::as_uint(const Node::Header &, const uint8_t *data, const size_t offset) const {
		return (unsigned int) *((uint16_t *)(data+offset));
	}

	std::string Decoder::UInt16::as_string(const Node::Header &header, const uint8_t *data, const size_t offset) const {
		return std::to_string(as_uint(header,data,offset));
	}

	std::string Decoder::Hex16::as_string(const Node::Header &header, const uint8_t *data, const size_t offset) const {
		std::stringstream stream;
		stream << "0x" << std::setfill('0') << std::setw(8) << hex << as_uint(header,data,offset);
		return stream.str();
	}

	std::string Decoder::LengthInBytes::as_string(const Node::Header &header, const uint8_t *data, const size_t offset) const {

		uint64_t value{as_uint64(header,data,offset)};
		if(!value) {
			return "";
		}

		static const struct {
			uint64_t value;
			const char *name;
		} units[8] = {
			{ 1LL,						"bytes"		},
			{ 1024LL,					"kB"		},
			{ 1048576LL,				"MB"		},
			{ 1073741824LL,				"GB"		},
			{ 1099511627776LL,			"TB"		},
			{ 1125899906842624LL,		"PB"		},
			{ 1152921504606846976LL,	"EB"		}
		};

		size_t selected = 0;
		for(size_t ix = 0; ix < (sizeof(units)/sizeof(units[0]));ix++) {
			if(value > units[ix].value) {
				selected = ix;
			} else {
				break;
			}
		}

		double converted = (double) value;
		converted /= ((double) units[selected].value);

		std::stringstream stream;

		stream << fixed << setprecision(0) << converted << " " << units[selected].name;

		return stream.str();

	}

	unsigned int Decoder::UInt8::as_uint(const Node::Header &header, const uint8_t *data, const size_t offset) const {
		if(offset > header.length) {
			return 0;
		}
		return (unsigned int) data[offset];
	}

	std::string Decoder::UInt8::as_string(const Node::Header &header, const uint8_t *data, const size_t offset) const {
		if(offset > header.length) {
			return "";
		}
		return std::to_string(as_uint(header,data,offset));
	}

 }

