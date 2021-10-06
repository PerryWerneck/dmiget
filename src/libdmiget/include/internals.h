/* SPDX-License-Identifier: LGPL-3.0-or-later */

/*
 * Copyright (C) 2021 Perry Werneck <perry.werneck@gmail.com>
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

 #pragma once

 #include <config.h>
 #include <dmiget/defs.h>
 #include <stdint.h>
 #include <stddef.h>
 #include <stdexcept>

 namespace DMI {

 	bool smbios3_decode(const uint8_t *entry, const uint8_t table);
 	bool checksum(const uint8_t *buf, size_t len);

	#if defined(BIGENDIAN)

		#define WORD(x)		(uint16_t)	((x)[0] + ((x)[1] << 8))
		#define DWORD(x)	(uint32_t) ((x)[0] + ((x)[1] << 8) + ((x)[2] << 16) + ((x)[3] << 24))
//		#define QWORD(x)	(uint64_t) (DWORD(x), DWORD(x + 4)))

	#else

		#define WORD(x)		(uint16_t)(*(const uint16_t *)(x))
		#define DWORD(x)	(uint32_t)(*(const uint32_t *)(x))
		#define QWORD(x)	(*(const uint64_t *)(x))

	#endif // BIGENDIAN

 }

