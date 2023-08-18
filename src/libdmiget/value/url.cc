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
  * @brief Find SMBios value using dmi:///url.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <smbios/defs.h>
 #include <smbios/node.h>
 #include <cstring>
 #include <stdexcept>
 #include <system_error>
 #include <iostream>
 #include <ctype.h>

 #include <private/decoders.h>

 using namespace std;
 using namespace SMBios;

 namespace SMBios {

	std::shared_ptr<Value> Value::find(const char *url) {

		if(!strncasecmp(url,"dmi:",4)) {
			url += 4;
		}

		while(*url && *url == '/') {
			url++;
		}

		if(!*url) {
			throw std::invalid_argument("Invalid URL");
		}

		string nodename;
		{
			const char *ptr = strchr(url,'/');
			if(!ptr) {
				throw std::invalid_argument("Invalid URL");
			}

			nodename = string{url,(size_t) (ptr-url) };

			url += nodename.size()+1;
		}

		if(nodename.empty() || !*url) {
			throw std::invalid_argument("Invalid URL");
		}

		SMBios::Node node{nodename.c_str()};

		size_t item = 1;
		if(node.multiple() && isdigit(*url)) {
			item = 0;
			while(*url != '/') {
				if(!isdigit(*url)) {
					throw std::invalid_argument("sub-node id should be number");
				}
				item *= 10;
				item += *url - '0';
			}
		}

		while(node) {
			if(--item == 0) {
				return node.find(url);
			}
			node.next(nodename.c_str());
		}

		throw system_error(ENOENT,system_category(),nodename.c_str());

 	}

 }

