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
  * @brief Implements python 'value' methods
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <private/python.h>
 #include <smbios/node.h>
 #include <smbios/value.h>
 #include <stdexcept>

 struct pyValuePrivate {
 	std::shared_ptr<SMBios::Value> value;
 };

 void dmiget_value_type_init() {
 }

 int dmiget_value_init(PyObject *self, PyObject *args, PyObject *) {

	if(!((pyValue *) self)->pvt) {
		((pyValue *) self)->pvt = new pyValuePrivate();
	}

	try {

		switch(PyTuple_Size(args)) {
		case 0: // Empty value.
			return 0;

		case 1:	// URL
			{
				const char *url = "";

				if (!PyArg_ParseTuple(args, "s", &url))
					throw runtime_error("Invalid argument");

				dmiget_set_value(self,SMBios::Value::find(url));

			}
			break;

		case 2:	// Node name, value name
			{
				const char *nodename = "";
				const char *valuename = "";

				if (!PyArg_ParseTuple(args, "ss", &nodename, &valuename))
					throw runtime_error("Invalid argument");

				dmiget_set_value(self,SMBios::Node{nodename}.find(valuename));

			}
			break;

		default:
			throw std::system_error(EINVAL, std::system_category());
		}

		return 0;

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in SMBios library");

	}

	return -1;

 }

 PyObject * dmiget_set_value(PyObject *self, shared_ptr<SMBios::Value> value) {
	((pyValue *) self)->pvt->value = value;
	return self;
 }

 void dmiget_value_finalize(PyObject *self) {

 	pyValuePrivate * pvt = ((pyValue *) self)->pvt;
	if(pvt) {
		delete pvt;
		((pyValue *) self)->pvt = nullptr;
	}

 }

 PyObject * dmiget_value_alloc(PyTypeObject *type, PyObject *, PyObject *) {
	return type->tp_alloc(type,0);
 }

 void dmiget_value_dealloc(PyObject * self) {
	Py_TYPE(self)->tp_free(self);
 }

 static PyObject * call(PyObject *self, const std::function<PyObject * (SMBios::Value &value)> &worker) {

	pyValuePrivate * pvt = ((pyValue *) self)->pvt;
	if(!pvt) {
		PyErr_SetString(PyExc_RuntimeError, "Object in invalid state");
		return NULL;
	}

	try {

		return worker(*pvt->value);

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in dmi module");

	}

	return NULL;

 }

 PyObject * dmiget_value_str(PyObject *self) {

	return call(self, [](SMBios::Value &value) {
		return PyUnicode_FromString(value.as_string().c_str());
	});

 }

 PyObject * dmiget_value_name(PyObject *self, void *) {

	return call(self, [](SMBios::Value &value) {
		return PyUnicode_FromString(value.name());
	});

 }

 PyObject * dmiget_value_description(PyObject *self, void *) {

	return call(self, [](SMBios::Value &value) {
		return PyUnicode_FromString(value.description());
	});

 }

 PyObject * dmiget_value_empty(PyObject *self, PyObject *) {

	if(!((pyValue *) self)->pvt) {
		return PyBool_FromLong(1);
	}

	return call(self, [](SMBios::Value &value) {
		return PyBool_FromLong(value ? 0 : 1);
	});

 }

 PyObject * dmiget_value_next(PyObject *self, PyObject *) {

	return call(self, [](SMBios::Value &v) {

		SMBios::Value *value = dynamic_cast<SMBios::Value *>(&v);

		if(!value) {
			throw runtime_error("Value is not iterable");
		}

		value->next();
		return PyBool_FromLong((*value) ? 1 : 0);

	});

 }

 int dmiget_value_bool(PyObject *self) {

	pyValuePrivate * pvt = ((pyValue *) self)->pvt;
	if(!pvt) {
		return 0;
	}

	try {

		return (*pvt->value) ? 1 : 0;

	} catch(const std::exception &e) {

			PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

			PyErr_SetString(PyExc_RuntimeError, "Unexpected error in smbios library");

	}

	return 0;

 }

 PyObject * dmiget_value_int(PyObject *self) {

	return call(self, [](SMBios::Value &value) {

		return PyLong_FromUnsignedLong(value.as_uint64());

	});

 }
