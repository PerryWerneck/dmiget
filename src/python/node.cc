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

 #include <private/python.h>
 #include <smbios/node.h>
 #include <stdexcept>

 struct pyNodePrivate {
	SMBios::Node node;
	pyNodePrivate(const char *name) : node{name} {
	}
 };

 void dmiget_node_type_init() {

 }

 int dmiget_node_init(PyObject *self, PyObject *args, PyObject *) {

	pyNodePrivate * pvt = ((pyNode *) self)->pvt;
	if(pvt) {
		delete pvt;	// Just in case
		((pyNode *) self)->pvt = NULL;
	}

	try {

		switch(PyTuple_Size(args)) {
		case 0:
			((pyNode *) self)->pvt = pvt = new pyNodePrivate{""};
			return 0;

		case 1:
			{
				const char *name = "";
				if (!PyArg_ParseTuple(args, "s", &name))
					throw runtime_error("Invalid argument");

				((pyNode *) self)->pvt = pvt = new pyNodePrivate{name};
			}
			return 0;

		default:
			throw runtime_error("Invalid arguments");
		}

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in core module");

	}

	return -1;

 }

 void dmiget_node_finalize(PyObject *self) {

	pyNodePrivate * pvt = ((pyNode *) self)->pvt;
	if(pvt) {
		delete pvt;
		((pyNode *) self)->pvt = nullptr;
	}

 }

 PyObject * dmiget_node_alloc(PyTypeObject *type, PyObject *, PyObject *) {
	return type->tp_alloc(type,0);
 }

 void dmiget_node_dealloc(PyObject * self) {
	pyNodePrivate * pvt = ((pyNode *) self)->pvt;
	if(pvt) {
		delete pvt;
		((pyNode *) self)->pvt = nullptr;
	}
	Py_TYPE(self)->tp_free(self);
 }

 static PyObject * call(PyObject *self, const std::function<PyObject * (SMBios::Node &node)> &worker) {

	pyNodePrivate * pvt = ((pyNode *) self)->pvt;
	if(!pvt) {
		PyErr_SetString(PyExc_RuntimeError, "Object in invalid state");
		return NULL;
	}

	try {

		return worker(pvt->node);

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in SMBios library");

	}

	return NULL;

 }

 PyObject * dmiget_node_name(PyObject *self) {

	return call(self, [](SMBios::Node &node) {
		return PyUnicode_FromString(node.name());
	});

 }

 PyObject * dmiget_node_str(PyObject *self) {

	return call(self, [](SMBios::Node &node) {
		return PyUnicode_FromString(node.description());
	});

 }

 PyObject * dmiget_node_name(PyObject *self, void *) {

	return call(self, [](SMBios::Node &node) {
		return PyUnicode_FromString(node.name());
	});

 }

 PyObject * dmiget_node_description(PyObject *self, void *) {

	return call(self, [](SMBios::Node &node) {
		return PyUnicode_FromString(node.description());
	});

 }

 PyObject * dmiget_node_multiple(PyObject *self, void *) {

	return call(self, [](SMBios::Node &node) {
		return PyBool_FromLong(node.multiple());
	});

 }

 PyObject * dmiget_node_empty(PyObject *self, PyObject *) {

	return call(self, [](SMBios::Node &node) {
		return PyBool_FromLong(node ? 0 : 1);
	});

 }

 PyObject * dmiget_node_type(PyObject *self, void *) {

	return call(self, [](SMBios::Node &node) {
		return PyLong_FromLong((unsigned long) node.type());
	});

 }

 PyObject * dmiget_node_handle(PyObject *self, void *) {

	return call(self, [](SMBios::Node &node) {
		return PyLong_FromLong((unsigned long) node.handle());
	});

 }

 PyObject * dmiget_node_size(PyObject *self, void *) {

	return call(self, [](SMBios::Node &node) {
		return PyLong_FromLong((unsigned long) node.size());
	});

 }

 PyObject * dmiget_node_next(PyObject *self, PyObject *args) {

	return call(self, [args](SMBios::Node &node) {

		switch(PyTuple_Size(args)) {
		case 0:
			node.next();
			return PyBool_FromLong(node ? 1 : 0);

		case 1:
			{
				const char *name = "";

				if (!PyArg_ParseTuple(args, "s", &name))
					throw runtime_error("Invalid argument");

				node.next(name);
			}
			return PyBool_FromLong(node ? 1 : 0);

		default:
			throw runtime_error("Invalid arguments");
		}
	});

 }

