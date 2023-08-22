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

 #pragma once

 #if defined(_WIN32)

	#define SMBIOS_API		__declspec (dllexport)
	#define SMBIOS_PRIVATE

 #else

	#define SMBIOS_API		__attribute__((visibility("default")))
	#define SMBIOS_PRIVATE	__attribute__((visibility("hidden")))

 #endif

 #ifdef _MSC_VER

	#include <string.h>
	#define strncasecmp  _strnicmp
	#define ftruncate    _chsize
	#define strtoull     _strtoui64
	#define strtoll      _strtoi64

	__inline int strcasecmp (const char *s1, const char *s2) {
		size_t size1 = strlen(s1);
		size_t size2 = strlen(s2);
		return _strnicmp(s1, s2, size2 > size1 ? size2 : size1);
	}

 #endif // _MSC_VER

 #ifdef __cplusplus
 namespace SMBios {

	class Data;
	class Node;
	class Value;

	namespace Decoder {

		struct Type;

	}

 }


 #endif // __cplusplus
