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
  * @brief Implements node object.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <iostream>
 #include <smbios/defs.h>
 #include <smbios/node.h>
 #include <private/data.h>
 #include <private/decoders.h>

 using namespace std;

 namespace SMBios {

	Node::Node(std::shared_ptr<Data> d, const int o)
		: data{d}, offset{o}, decoder{Decoder::get(d,o)} {
		setup(0);
	}

	Node::Node() : Node{Data::factory(),-1} {
	}

	Node::Node(uint8_t type, int index) : Node{} {

		if(header.type != type) {
			next(type);
		}

		while(index-- > 0 && *this) {
			next(type);
		}

	}

	Node::Node(const char *name, int index) : Node{Decoder::get(name)->type,index} {
	}

	Node Node::factory(const char *filename, const char *name, int index) {

		auto data = Data::factory(filename);
		Node node{data};

		if(name && *name) {
			uint8_t type{Decoder::get(name)->type};
			if(node.header.type != type) {
				node.next(type,index);
			}
		}

		return node;
	}

	Node::operator bool() const {
		return offset >= 0 && header.length >= 4 && header.type != 127 && decoder;
	}

	Node & Node::setup(int offset) {

		this->offset = offset;
		if(offset < 0) {
			header.type = 0xFF;
			header.length = 0;
			header.handle = 0xffff;
			return *this;
		}

		const uint8_t *ptr = data->get(offset);
		header.type = ptr[0];
		header.length = ptr[1];
		header.handle = WORD(ptr+2);

		if(header.length < 4 || header.type == 127) {
			offset = -1;
			return *this;
		}

		decoder = Decoder::get(header.type);

		return *this;
	}

	Node & Node::rewind() {
		index = 0;
		return setup(0);
	}

	const char * Node::name() const noexcept {
		if(*this) {
			return decoder->name;
		}
		return "";
	}

	const char * Node::description() const noexcept {
		if(*this) {
			return decoder->description;
		}
		return "";
	}

	bool Node::multiple() const noexcept {
		if(*this) {
			return decoder->multiple;
		}
		return false;
	}

	Node & Node::operator=(const uint8_t type) {
		rewind();
		if(header.type != type) {
			return next(type);
		}
		return *this;
	}

	Node & Node::operator=(const char *name) {
		return operator=(Decoder::get(name)->type);
	}

	std::shared_ptr<Value> Node::operator[](size_t index) const {

		if(!*this) {
			throw std::system_error(ENODATA,std::system_category());
		}

		for(size_t item = 0; decoder->itens[item].name; item++) {
			if(item == index) {
				return decoder->factory(*decoder,data,offset,item);
			}
		}

		throw std::system_error(ENOENT,std::system_category());

	}

	std::shared_ptr<Value> Node::operator[](const char *name) const {

		if(!*this) {
			throw std::system_error(ENODATA,std::system_category());
		}

		for(size_t item = 0; decoder->itens[item].name; item++) {
			if(!strcasecmp(name,decoder->itens[item].name)) {
				return decoder->factory(*decoder,data,offset,item);
			}
		}

		throw std::system_error(ENOENT,std::system_category());

	}

	Value::Iterator Node::begin() {

		if(*this && decoder && decoder->itens && decoder->itens[0].name) {
			return Value::Iterator{decoder->factory(*decoder,data,offset,0)};
		}

		return end();

	}

	Value::Iterator Node::end() {
		return Value::Iterator{};
	}

	std::shared_ptr<Value> Node::find(const char *url) const {

		if(!*this) {
			throw std::system_error(ENODATA,std::system_category());
		}

		string name;
		const char *ptr = strchr(url,'/');
		if(ptr) {
			name = string{url,(size_t) (ptr-url) };
		} else {
			name = url;
		}
		url += name.size()+1;

		for(size_t item = 0; decoder->itens[item].name; item++) {
			if(!strcasecmp(name.c_str(),decoder->itens[item].name)) {
				return decoder->factory(*decoder,data,offset,item);
			}
		}

		throw std::system_error(ENOENT,std::system_category());

	}

 }
