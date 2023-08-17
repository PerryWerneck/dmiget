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
  * @brief Implements node for_each methods.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <smbios/defs.h>
 #include <smbios/node.h>
 #include <private/decoders.h>
 #include <functional>
 #include <cstring>

 namespace SMBios {

	bool Node::for_each(const std::function<bool(const Node &node)> &call) {

		for(Node node;node;node.next()) {
			if(call(node)) {
				return true;
			}
		}

		return false;

	}

	bool Node::for_each(const std::function<bool(const Node &node, size_t index)> &call) {

		size_t indexes[0x0100];
		memset(indexes,0,sizeof(indexes));

		for(Node node;node;node.next()) {

			if(node.decoder->multiple) {
				if(call(node,++indexes[node.decoder->type])) {
					return true;
				}
			} else {
				if(call(node,0)) {
					return true;
				}
			}

		}

		return false;

	}

	bool Node::for_each(uint8_t type,const std::function<bool(const Node &node)> &call) {

		for(Node node;node;node.next()) {
			if(node.header.type == type && call(node)) {
				return true;
			}
		}

		return false;

	}

	bool Node::for_each(const char *name,const std::function<bool(const Node &node)> &call) {
		return for_each(Decoder::get(name)->type,call);
	}

	bool Node::for_each(const std::function<bool(const Value &v)> &call) {

		if(!*this) {
			return false;
		}

		for(size_t item = 0; decoder->items[item].name; item++) {
			auto value = decoder->items[item].ValueFactory(data,offset,item);
			if(call(*value)) {
				return true;
			}
		}
		return false;

	}

	bool Node::for_each(const std::function<bool(const Node &node, const size_t index, const Value &v)> &call) {

		size_t indexes[0x0100];
		memset(indexes,0,sizeof(indexes));

		for(Node node;node;node.next()) {

			size_t index = 0;
			if(node.decoder->multiple) {
				index = ++indexes[node.decoder->type];
			}

			if(node.for_each([&node,index,&call](const Value &value){
				return call(node,index,value);
			})) {
				return true;
			};
		}

		return false;
	}

 }
