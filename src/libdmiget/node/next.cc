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
  * @brief Implements node::next() methods.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <smbios/defs.h>
 #include <smbios/node.h>
 #include <private/data.h>
 #include <private/decoders.h>

 using namespace std;

 namespace SMBios {

	Node & Node::next() {

		if(!*this) {
			return *this;
		}

		index++;
		if((data->count() && index >= data->count())) {
			offset = -1;
			return *this;
		}

		// Look for the next handle
		const uint8_t *buf = data->get(0);
		const uint8_t *next = buf+offset+header.length;

		while ((unsigned long)(next - buf + 1) < data->size() && (next[0] != 0 || next[1] != 0))
			next++;
		next += 2;

		offset = (next - buf);

		if( (offset+4) > ((int) data->size()) ) {
			return setup(-1);
		}

		return setup(offset);
	}

	Node & Node::next(uint8_t type, size_t count) {

		while(*this && count--) {
			next();
			while(*this && header.type != type) {
				next();
			}
		}

		return *this;
	}

	Node & Node::next(const char *name,size_t count) {

		if(name && *name) {
			return next(Decoder::get(name)->type, count);
		}

		while(count--) {
			next();
		}

		return *this;
	}

 }

