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
  * @brief Implement TPM decoders.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <private/decoders.h>
 #include <private/decoders/tools.h>
 #include <private/decoders/tpm.h>

 #include <string>

 using namespace std;

 namespace SMBios {

	std::string Decoder::TPMVendorID::as_string(const Node::Header &, const uint8_t *ptr, const size_t offset) const {
		ptr += offset;
		char value[4];
		memcpy(value,ptr,3);
		value[3] = 0;
		return value;
	}

	std::string Decoder::TPMSpecification::as_string(const Node::Header &, const uint8_t *ptr, const size_t offset) const {
		ptr += offset;
		string value = std::to_string((int) ptr[0]);
		value += '.';
		value += std::to_string((int) ptr[1]);
		return value;
	}

	std::string Decoder::TPMRevision::as_string(const Node::Header &, const uint8_t *ptr, const size_t) const {
		string value;

		switch(ptr[8]) {
		case 1:
			value = to_string((int) ptr[0x0C]);
			value += '.';
			value += to_string((int) ptr[0x0D]);
			break;

		case 2:
			value = to_string((int) (DWORD(ptr + 0x0A) >> 16));
			value += '.';
			value += to_string((int) (DWORD(ptr + 0x0A) & 0xFFFF));
			break;

		default:
			value = "Unknown";

		}

		return value;
	}

 }

