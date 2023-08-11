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

 #include <private/decoders.h>
 #include <smbios/node.h>
 #include <string>
 #include <cstring>

 using namespace std;

 namespace SMBios {

	std::string u64::as_memory_size(int shift) const {

		unsigned long capacity;
		uint16_t split[7];
		static const char *unit[8] = {
			"bytes", "kB", "MB", "GB", "TB", "PB", "EB", "ZB"
		};
		int i;

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
		for (i = 6; i > 0; i--)
		{
			if (split[i])
				break;
		}
		if (i > 0 && split[i - 1])
		{
			i--;
			capacity = split[i] + (split[i + 1] << 10);
		}
		else
			capacity = split[i];

		return std::to_string(capacity) + " " + unit[i + shift];

	}

 }
