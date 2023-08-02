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
  * @brief Python tools methods.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <private/python.h>
 #include <stdexcept>

 using namespace std;

 PyObject * PyObjectByName(const char *name) {

	PyObject * dict = PyModule_GetDict(smbios_module);
	if(!dict) {
		throw runtime_error("Unable to get module dictionary");
	}

	PyObject * python_class = PyDict_GetItemString(dict, name);

	if(!python_class) {
		throw runtime_error("Unable to get value class");
	}

	if(!PyCallable_Check(python_class)) {
		throw runtime_error("Value class is not callable");
	}

	PyObject * object = PyObject_CallObject(python_class, nullptr);

	return object;
 }

