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
  * @brief Common methods to smbios data class
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #ifdef _WIN32
	#include <windows.h>
 #endif // _WIN32

 #ifdef _MSC_VER
	#include <io.h>
	#pragma warning(suppress : 4996)
 #endif // _MSC_VER

 #include <private/data.h>
 #include <stdexcept>
 #include <system_error>

 #ifdef HAVE_UNISTD_H
	#include <unistd.h>
 #endif // HAVE_UNISTD_H

 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <cstring>
 #include <iostream>

 using namespace std;

 namespace SMBios {

 }


