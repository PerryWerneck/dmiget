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

 #ifdef HAVE_UNISTD_H
	#include <unistd.h>
 #endif // HAVE_UNISTD_H

 #include <private/python.h>
 #include <smbios/node.h>
 #include <smbios/value.h>
 #include <stdexcept>
 #include <vector>

 using namespace std;

 struct pyNodePrivate {

	SMBios::Node node;

	pyNodePrivate() {
	}

	pyNodePrivate(const char *name) : node{name} {
	}

	pyNodePrivate(SMBios::Node &n) : node{n} {
	}

 };

 void dmiget_node_type_init() {

 }

 int dmiget_node_init(PyObject *self, PyObject *args, PyObject *) {

	try {

		pyNodePrivate * pvt = ((pyNode *) self)->pvt;
		if(pvt) {
			delete pvt;	// Just in case
			((pyNode *) self)->pvt = NULL;
		}

		switch(PyTuple_Size(args)) {
		case 0:	// Create an empty node.
			return 0;

		case 1:
			{
				const char *name = "";

				if (!PyArg_ParseTuple(args, "s", &name))
					throw runtime_error("Invalid argument");

				if(name && *name) {
					((pyNode *) self)->pvt = pvt = new pyNodePrivate{name};
				} else {
					((pyNode *) self)->pvt = pvt = new pyNodePrivate{};
				}

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

	try {

		pyNodePrivate * pvt = ((pyNode *) self)->pvt;
		if(!pvt) {
			((pyNode *) self)->pvt = pvt = new pyNodePrivate{};
		}

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

	if(!((pyNode *) self)->pvt) {
		return PyBool_FromLong(1);
	}

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

 PyObject * dmiget_node_value(PyObject *self, PyObject *args) {

 	return call(self, [args](SMBios::Node &node) {

		const char *name = "";

		switch(PyTuple_Size(args)) {
		case 0:
			break;

		case 1:
			if (!PyArg_ParseTuple(args, "s", &name))
				throw runtime_error("Invalid argument");
			break;

		default:
			throw runtime_error("Invalid arguments");
		}

		PyObject *object = PyObjectByName("value");
		dmiget_set_value(object,node.find(name));

		return object;
 	});

 }

void dmiget_set_node(PyObject *self, SMBios::Node &node) {
	pyNodePrivate * pvt = ((pyNode *) self)->pvt;
	if(pvt) {
		delete pvt;
	}
	((pyNode *) self)->pvt = new pyNodePrivate{node};
 }

 PyObject * dmiget_node_values(PyObject *self, PyObject *) {

 	return call(self, [](SMBios::Node &node) {

		PyObject *pynodes = PyList_New(0);

		node.for_each([pynodes](const SMBios::Value &value){
			PyList_Append(pynodes,dmiget_set_value(PyObjectByName("value"),value.clone()));
			return false;
		});

		return pynodes;

 	});

 }

 PyObject * pydmi_get_nodes(PyObject *, PyObject *args) {

	try {

		std::string name;

		switch(PyTuple_Size(args)) {
		case 0:
			break;

		case 1:
			{
				const char *ptr = "";

				if (!PyArg_ParseTuple(args, "s", &ptr))
					throw runtime_error("Invalid argument");

				name = ptr;
			}
			break;

		default:
			throw runtime_error("Invalid arguments");
		}

		PyObject *pynodes = PyList_New(0);
		SMBios::Node::for_each(name.c_str(),[pynodes](const Node &node){
			PyObject *pyobject = PyObjectByName("node");
			dmiget_set_node(pyobject,const_cast<Node &>(node));
			PyList_Append(pynodes,pyobject);
			return false;
		});

		return pynodes;

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in SMBios library");

	}

	return NULL;

 }

 PyObject * pydmi_get_values(PyObject *self, PyObject *args) {
	try {

		std::string name;

		switch(PyTuple_Size(args)) {
		case 0:
			break;

		case 1:
			{
				const char *ptr = "";

				if (!PyArg_ParseTuple(args, "s", &ptr))
					throw runtime_error("Invalid argument");

				name = ptr;
			}
			break;

		default:
			throw runtime_error("Invalid arguments");
		}

		PyObject *pynodes = PyList_New(0);
		SMBios::Node::for_each([pynodes,name](const Node &node){

			node.for_each([pynodes,name](const SMBios::Value &value){
				if(name.empty() || value == name.c_str()) {
					PyList_Append(pynodes,dmiget_set_value(PyObjectByName("value"),value.clone()));
				}
				return false;
			});

			return false;
		});

		return pynodes;

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in SMBios library");

	}

	return NULL;

 }

 int dmiget_node_bool(PyObject *self) {

	pyNodePrivate * pvt = ((pyNode *) self)->pvt;
	if(!pvt) {
		return 0;
	}

	try {

		return (pvt->node ? 1 : 0);

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in smbios library");

	}

	return 0;

 }

 PyObject * dmiget_node_int(PyObject *self) {

	return call(self, [](SMBios::Node &node) {

		if(node) {
			return PyLong_FromLong(node.type());
		}

		return PyLong_FromLong(-1);

	});

 }
