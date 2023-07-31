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
  * @brief Implements abstract value.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <private/smbios.h>
 #include <smbios/value.h>
 #include <private/constants.h>

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

 	Value::operator bool() const {
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

	std::string Value::to_string() const {
		if(info && info[item].name && *info[item].name) {
			return info[item].decoder.to_string((*data)[offset],(size_t) info[item].offset);
		}
		return "";
	}

 }
