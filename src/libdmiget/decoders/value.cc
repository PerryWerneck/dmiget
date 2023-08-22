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
  * @brief Declare standard decoder item.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <smbios/defs.h>
 #include <private/data.h>
 #include <smbios/value.h>
 #include <private/decoders.h>
 #include <string>
 #include <ctype.h>

 using namespace std;

 namespace SMBios {

	Decoder::Value::Value(const Decoder::Type &t, std::shared_ptr<Data> d, int o, size_t i)
		: type{t}, data{d}, offset{o}, item{i} {
	}

	Decoder::Value::~Value() {
	}

	std::shared_ptr<SMBios::Value> Decoder::Value::clone() const {
		return make_shared<Decoder::Value>(type,data,offset,item);
	}

	std::shared_ptr<SMBios::Value> Decoder::Value::factory(const Decoder::Type &type, std::shared_ptr<Data> data, int offset, size_t item) {
		return make_shared<Decoder::Value>(type,data,offset,item);
	}

	bool Decoder::Value::empty() const {
		return !type.itens[item].name || offset < 0;
	}

	const char * Decoder::Value::name() const noexcept {
		if(!empty()) {
			return type.itens[item].name;
		}
		return "";
	}

	const char * Decoder::Value::description() const noexcept {
		if(!empty()) {
			return type.itens[item].description;
		}
		return "";
	}

	std::string Decoder::Value::as_string() const {
		if(empty()) {
			return "";

		}
		const uint8_t *ptr = data->get(offset);
		return type.itens[item].worker.as_string(*((const Node::Header *) ptr), ptr, type.itens[item].offset);
	}

	uint64_t Decoder::Value::as_uint64() const {
		if(empty()) {
			return 0;

		}
		const uint8_t *ptr = data->get(offset);
		return type.itens[item].worker.as_uint64(*((const Node::Header *) ptr), ptr, type.itens[item].offset);
	}

	unsigned int Decoder::Value::as_uint() const {
		if(empty()) {
			return 0;

		}
		const uint8_t *ptr = data->get(offset);
		return type.itens[item].worker.as_uint(*((const Node::Header *) ptr), ptr, type.itens[item].offset);
	}

	SMBios::Value & Decoder::Value::next() {

		if(empty()) {
			return *this;
		}

		item++;
		return *this;
	}

 }
