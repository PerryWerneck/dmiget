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
  * @brief Implements python 'node' object.
  */

 #include <config.h>
 #include <dmiget/table.h>
 #include "private.h"

 struct pyNodePrivate {
 	std::shared_ptr<DMIget::Value> value;
 };

 void dmiget_value_type_init() {

 }

 int dmiget_value_init(PyObject *self, PyObject *args, PyObject *) {

	pyNodePrivate * pvt = ((pyNode *) self)->pvt;
	if(!pvt) {
		((pyNode *) self)->pvt = pvt = new pyNodePrivate{};
	}

	try {

		const char *node = "";
		const char *name = "";

		if (!PyArg_ParseTuple(args, "ss", &node, &name))
			throw runtime_error("Invalid argument");

		if(!(node && *node)) {
			throw runtime_error("Node name is empty or invalid");
		}

		if(!(name && *name)) {
			throw runtime_error("Value name is empty or invalid");
		}

		pvt->value = DMIget::Table{}.find(node, name);

		return 0;

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in core module");

	}

	return -1;

 }

 void dmiget_value_finalize(PyObject *self) {
	pyNodePrivate * pvt = ((pyNode *) self)->pvt;
	if(pvt) {
		pvt->value.reset();
	}
 }

 PyObject * dmiget_value_alloc(PyTypeObject *type, PyObject *, PyObject *) {
	return type->tp_alloc(type,0);
 }

 void dmiget_value_dealloc(PyObject * self) {
	pyNodePrivate * pvt = ((pyNode *) self)->pvt;
	if(pvt) {
		delete pvt;
		((pyNode *) self)->pvt = nullptr;
	}
	Py_TYPE(self)->tp_free(self);
 }
