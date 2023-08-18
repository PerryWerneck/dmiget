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
  * @brief Implements OEMString value.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 /*
 #include <private/oemstring.h>
 #include <string>
 #include <cstdint>
 #include <ctype.h>
 #include <cstring>

 using namespace std;

 namespace SMBios {

	OEMString::OEMString(size_t i, const char *s) : index{i}, ptr{s}, oname{std::to_string(i)} {
	}

 	std::string OEMString::as_string() const {
 		if(ptr && *ptr) {
			return string{ptr};
 		}
 		return "";
	}

	const char * OEMString::name() const noexcept {
		return oname.c_str();
	}

	const char * OEMString::description() const noexcept {
		return "OEM String";
	}

	bool OEMString::valid() const  {
		return ptr && *ptr;
	}

	uint64_t OEMString::as_uint64() const  {
		uint64_t rc = 0;
		if(ptr && *ptr) {
			for(const char *p = ptr;isdigit(*p);p++) {
				rc *= 10;
				rc += (*p - '0');
			}
		}
		return rc;
	}

	unsigned int OEMString::as_uint() const  {
		unsigned int rc = 0;
		if(ptr && *ptr) {
			for(const char *p = ptr;isdigit(*p);p++) {
				rc *= 10;
				rc += (*p - '0');
			}
		}
		return rc;
	}

	Abstract::Value & OEMString::next() {
		if(ptr && *ptr) {
			ptr += strlen(ptr);
			ptr++;
			index++;
			oname = std::to_string(index);
		}
		return *this;
	}

 }
 */
