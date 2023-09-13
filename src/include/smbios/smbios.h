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
  * @brief Declare 'C' API.
  */

 #pragma once
 #include <smbios/defs.h>

 #ifdef __cplusplus
	extern "C" {
 #endif // __cplusplus

 /// @brief Get value from SMBios URL
 /// @param url the URL in the format dmi:///[NODE]/[VALUE]
 /// @return NULL on failure, the value on success (release it using free())
 SMBIOS_API char * dmi_get_value_from_url(const char *url);

 /// @brief Get value from SMBios using node & value names
 /// @param node The node name
 /// @param value The value name.
 /// @return NULL on failure, the value on success (release it using free())
 SMBIOS_API char * dmi_get_value(const char *node, const char *name);

 #ifdef __cplusplus
	}
 #endif // __cplusplus
