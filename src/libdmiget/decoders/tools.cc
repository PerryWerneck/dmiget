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
  * @brief Misc tools for decoders.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <private/decoders/tools.h>

 #include <string>

 using namespace std;

 namespace SMBios {

	namespace Decoder {

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

		 std::string u64::as_memory_size_string(int shift) const {

			unsigned long capacity;
			int i;

			decode_memory_size(capacity,i);
			return to_string(capacity) + " " + units[i + shift].name;

		 }

		 uint64_t u64::as_memory_size_bytes(int shift) const {

			unsigned long capacity;
			int i;

			decode_memory_size(capacity,i);
			return ((uint64_t) capacity) * units[i + shift].value;

		 }

		void u64::decode_memory_size(unsigned long &capacity, int &i) const {

			uint16_t split[7];

			//
			// We split the overall size in powers of thousand: EB, PB, TB, GB,
			// MB, kB and B. In practice, it is expected that only one or two
			// (consecutive) of these will be non-zero.
			//
			split[0] = this->l & 0x3FFUL;
			split[1] = (this->l >> 10) & 0x3FFUL;
			split[2] = (this->l >> 20) & 0x3FFUL;
			split[3] = ((this->h << 2) & 0x3FCUL) | (this->l >> 30);
			split[4] = (this->h >> 8) & 0x3FFUL;
			split[5] = (this->h >> 18) & 0x3FFUL;
			split[6] = this->h >> 28;

			//
			// Now we find the highest unit with a non-zero value. If the following
			// is also non-zero, we use that as our base. If the following is zero,
			// we simply display the highest unit.
			//
			for (i = 6; i > 0; i--) {
				if (split[i])
					break;
			}

			if (i > 0 && split[i - 1]) {
				i--;
				capacity = split[i] + (split[i + 1] << 10);
			} else {
				capacity = split[i];
			}

		}

	}

 }
