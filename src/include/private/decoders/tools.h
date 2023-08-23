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

/*
 * Based on dmidecode
 *
 * Copyright (C) 2000-2002 Alan Cox <alan@redhat.com>
 * Copyright (C) 2002-2020 Jean Delvare <jdelvare@suse.de>
 *
 */

 /**
  * @brief Brief description of this source.
  */

 #pragma once

 #include <smbios/defs.h>
 #include <private/decoders.h>

 namespace SMBios {

 	namespace Decoder {

		struct u64 {
#ifdef BIGENDIAN
			uint32_t h = 0;
			uint32_t l = 0;
#else
			uint32_t l = 0;
			uint32_t h = 0;
#endif
			void decode_memory_size(unsigned long &capacity, int &i) const;
			std::string as_memory_size_string(int shift = 1) const;
			uint64_t as_memory_size_bytes(int shift = 1) const;

		};

 	}

 }
