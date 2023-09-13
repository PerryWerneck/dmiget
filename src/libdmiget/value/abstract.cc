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

 #include <smbios/value.h>
 #include <smbios/node.h>
 #include <stdexcept>
 #include <smbios/smbios.h>

 using namespace std;

 namespace SMBios {

	bool Value::operator==(const Value &src) const noexcept {
		return offset == src.offset && item == src.item;
	}

	bool Value::operator==(const char *name) const noexcept {
		if(*this && name && *name) {
			return strcasecmp(this->name(),name) == 0;
		}
		return false;
	}

	uint64_t Value::as_uint64() const {
		return as_uint();
	}

	std::shared_ptr<Value> Value::clone() const {
		throw runtime_error("Value is not a cloneable");
	}

	unsigned int Value::as_uint() const {
		throw runtime_error("Value is not a number");
	}

	Value & Value::next() {
		throw runtime_error("Value is not iteratable");
	}

 }

 SMBIOS_API char * dmi_get_value_from_url(const char *url) {

	char *rc = NULL;

	try {

		if(url && *url) {

			rc = strdup(SMBios::Value::find(url)->as_string().c_str());

		}

	} catch(...) {

		return NULL;

	}

	return rc;

 }

 SMBIOS_API char * dmi_get_value(const char *node, const char *name) {

	char *rc = NULL;

	try {

		if(node && name && *node && *name) {

			rc = strdup(SMBios::Node{node}[name]->as_string().c_str());

		}

	} catch(...) {

		return NULL;

	}

	return rc;

 }


