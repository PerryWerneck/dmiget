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
  * @brief Implements basic value.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <private/data.h>
 #include <smbios/value.h>
 #include <private/constants.h>
 #include <cstring>
 #include <system_error>

 using namespace std;

 namespace SMBios {

	Value::Value(const Value &src)
		: data{src.data}, offset{src.offset}, info{src.info}, item{src.item} {
	}

	Value::Value(const Value *src)
		: data{src->data}, offset{src->offset}, info{src->info}, item{src->item} {
	}

	Value::Value(std::shared_ptr<Data> d, size_t o, const Value::Info *t, size_t i)
		: data{d}, offset{o}, info{t}, item{i} {
	}

	Value::~Value() {
	}

	Value & Value::operator=(const Value & src) {
		data = src.data;
		offset = src.offset;
		info = src.info;
		item = src.item;
		return *this;
	}

	Value & Value::operator=(const char *name) {

		for(size_t itn = 0; info[itn].name; itn++) {
			if(!strcasecmp(info[itn].name,name)) {
				item = itn;
				return *this;
			}
		}

		throw std::system_error(ENOENT,std::system_category(),name);

	}

	Value & Value::operator=(const size_t index) {

		for(size_t itn = 0; info[itn].name; itn++) {
			if(itn == index) {
				item = itn;
				return *this;
			}
		}

		throw std::system_error(EINVAL,std::system_category());
	}

 	bool Value::valid() const {
		return info && info[item].name && *info[item].name;
	}

	Value & Value::next() {
		if(info && info[item].name) {
			item++;
		}
		return *this;
	}

	const char * Value::name() const noexcept {
		if(info && info[item].name) {
			return info[item].name;
		}
		return "";
	}

	const char * Value::description() const noexcept {
		if(info && info[item].description) {
			return info[item].description;
		}
		return "";
	}

	std::string Value::as_string() const {
		if(info && info[item].name && *info[item].name) {
			return info[item].decoder.as_string((*data)[offset],(size_t) info[item].offset);
		}
		return "";
	}

	unsigned int Value::as_uint() const {
		if(info && info[item].name && *info[item].name) {
			return info[item].decoder.as_uint((*data)[offset],(size_t) info[item].offset);
		}
		return 0;
	}

	uint64_t Value::as_uint64() const {
		if(info && info[item].name && *info[item].name) {
			return info[item].decoder.as_uint64((*data)[offset],(size_t) info[item].offset);
		}
		return 0;
	}

 }

