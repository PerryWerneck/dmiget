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

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <internals.h>
 #include <cstring>
 #include <iostream>

 using namespace std;

 namespace DMIget {

	void String::set(const char *bp, bool filter) {

		if(*bp) {

			char * converted = strdup(bp);

			if(filter) {
				for(char *ptr = converted; *ptr; ptr++) {
					if ( *ptr < 32 || *ptr >= 127) {
						*ptr = '.';
					}
				}
			}

			// TODO: Strip converted.

			str.assign(converted);

			free(converted);

		} else {
			str.clear();
		}

	}

	String::String(const char *bp, bool filter) {
		set(bp,filter);
	}

	String::String(const Header &header, uint8_t s, bool filter) {

		const char *bp = (const char *) header.data;

		bp += header.length;
		while (s > 1 && *bp) {
			bp += strlen(bp);
			bp++;
			s--;
		}

		set(bp,filter);

	}

	String::~String() {
	}

	std::string String::as_string() const {
		return this->str;
	}

 }
