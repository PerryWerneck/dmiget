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
		return type.itens[item].worker.as_string(*((const Node::Header *) ptr), ptr, offset);
	}

	uint64_t Decoder::Value::as_uint64() const {
		if(empty()) {
			return 0;

		}
		const uint8_t *ptr = data->get(offset);
		return type.itens[item].worker.as_uint64(*((const Node::Header *) ptr), ptr, offset);
	}

	unsigned int Decoder::Value::as_uint() const {
		if(empty()) {
			return 0;

		}
		const uint8_t *ptr = data->get(offset);
		return type.itens[item].worker.as_uint(*((const Node::Header *) ptr), ptr, offset);
	}

	SMBios::Value & Decoder::Value::next() {

		if(empty()) {
			return *this;
		}

		item++;
		return *this;
	}

	/*
	std::shared_ptr<SMBios::Value> Decoder::Item::ValueFactory(std::shared_ptr<Data> data, size_t offset, size_t item) const {

		/// @brief SMBIos value using decoders to translate data.
		class Value : public SMBios::Value {
		private:
			const Decoder::Item *decoder;
			std::shared_ptr<Data> data;

		public:
			Value(const Decoder::Item *d, std::shared_ptr<Data> p, int o, size_t i)
				: SMBios::Value{o,i}, decoder{d}, data{p} {
			}

			virtual ~Value() {
			}

			const char *name() const noexcept override {
				return decoder->name;
			}

			const char *description() const noexcept override {
				return decoder->description;
			}

			std::string as_string() const override {
				if(offset >= 0) {
					const uint8_t *ptr = data->get(offset);
					return decoder->as_string( *((const Node::Header *) ptr), ptr);
				}
				return "";
			}

			bool empty() const override {
				return offset < 0 || !(decoder->name && *decoder->name);
			}

			uint64_t as_uint64() const override {
				if(offset >= 0) {
					const uint8_t *ptr = data->get(offset);
					return decoder->as_uint64( *((const Node::Header *) ptr), ptr);
				}
				return 0;
			}

			unsigned int as_uint() const override {
				if(offset >= 0) {
					const uint8_t *ptr = data->get(offset);
					return decoder->as_uint( *((const Node::Header *) ptr), ptr);
				}
				return 0;
			}

			Value & next() override {
				if(offset >= 0 && decoder->name && *decoder->name) {
					decoder++;
					item++;
				}
				return *this;
			}

		};

		return make_shared<Value>(this,data,offset,item);

	}

	std::string Decoder::Item::as_string(const Node::Header &, const uint8_t *) const {
		return "";
	}

	unsigned int Decoder::Item::as_uint(const Node::Header &header, const uint8_t *ptr) const {
		string str{as_string(header,ptr)};

		unsigned int rc = 0;
		for(const char *ptr = str.c_str();*ptr && isdigit(*ptr);ptr++) {
			rc *= 10;
			rc += ('0' - *ptr);
		}

		return rc;
	}

	uint64_t Decoder::Item::as_uint64(const Node::Header &header, const uint8_t *ptr) const {
		string str{as_string(header,ptr)};

		uint64_t rc = 0;
		for(const char *ptr = str.c_str();*ptr && isdigit(*ptr);ptr++) {
			rc *= 10;
			rc += ('0' - *ptr);
		}

		return rc;

	}
	*/

 }
