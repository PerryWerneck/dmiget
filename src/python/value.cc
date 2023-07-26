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

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <dmiget/table.h>
 #include <dmiget/value.h>
 #include "private.h"

 struct pyNodePrivate {
	std::string node;
	std::string name;
 };

 void dmiget_value_type_init() {

	// Properties:
	//		url
	//		node
	//		name
	//		description
	//		value

	// struct PyGetSetDef attrs[] = {
	// }

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

		pvt->node = node;
		pvt->name = name;

		return 0;

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in core module");

	}

	return -1;

 }

 void dmiget_value_finalize(PyObject *self) {
 }

 PyObject * dmiget_value_alloc(PyTypeObject *type, PyObject *, PyObject *) {
	return type->tp_alloc(type,0);
 }

 void dmiget_value_dealloc(PyObject * self) {
	Py_TYPE(self)->tp_free(self);
 }

 static PyObject * call(PyObject *self, const std::function<std::string (const DMI::Value &value)> &worker) {

	pyNodePrivate * pvt = ((pyNode *) self)->pvt;
	if(!pvt) {
		PyErr_SetString(PyExc_RuntimeError, "Object in invalid state");
		return NULL;
	}

	try {
		DMIget::Table table;

		auto value = table.find(pvt->node.c_str(),pvt->name.c_str());
		if(!value) {
			throw runtime_error("Error finding SMBIOS value");
		}

		return PyUnicode_FromString(worker(*value).c_str());

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in dmi module");

	}

	return NULL;

 }


 PyObject * dmiget_value_str(PyObject *self) {

	return call(self,[](const DMI::Value &value){
		return value.as_string();
	});

 }

 PyObject * dmiget_value_url(PyObject *self) {
	return call(self,[](const DMI::Value &value){
		return value.url();
	});
 }

 PyObject * dmiget_value_node_name(PyObject *self) {
	return call(self,[](const DMI::Value &value){
		return value.node();
	});
 }

 PyObject * dmiget_value_name(PyObject *self) {
	return call(self,[](const DMI::Value &value){
		return value.name();
	});
 }

 PyObject * dmiget_value_description(PyObject *self) {
	return call(self,[](const DMI::Value &value){
		return value.description();
	});
 }

 DMIGET_PRIVATE PyObject * dmiget_value_getattr(PyObject *self, char *name) {

	return call(self,[name](const DMI::Value &value){

		if(!strcasecmp(name,"url")) {
			return value.url();
		}

		if(!strcasecmp(name,"node")) {
			return string{value.node()};
		}

		if(!strcasecmp(name,"name")) {
			return string{value.name()};
		}

		if(!strcasecmp(name,"description")) {
			return string{value.description()};
		}

		if(!strcasecmp(name,"value")) {
			return value.as_string();
		}

		throw runtime_error("Invalid attribute");

	});


 }

 DMIGET_PRIVATE int dmiget_value_setattr(PyObject *self, char *name, PyObject *value) {
	pyNodePrivate * pvt = ((pyNode *) self)->pvt;
	if(!pvt) {
		PyErr_SetString(PyExc_RuntimeError, "Object in invalid state");
	}

 }
