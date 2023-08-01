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

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <smbios/defs.h>
 #include <private/python.h>

 PyObject * smbios_module = NULL;

 static void cleanup(PyObject *module);

 static PyMethodDef dmiget_node_methods[] = {

        {
			.ml_name = "next",
			.ml_meth = dmiget_node_next,
			.ml_flags = METH_VARARGS,
			.ml_doc = "Move to next node"
        },

		{
			.ml_name = "empty",
			.ml_meth = dmiget_node_empty,
			.ml_flags = METH_NOARGS,
			.ml_doc = "True if the node is empty"
		},

		{
			.ml_name = "value",
			.ml_meth = dmiget_node_value,
			.ml_flags = METH_VARARGS,
			.ml_doc = "Get node value"
		},

		{
			.ml_name = "values",
			.ml_meth = dmiget_node_values,
			.ml_flags = METH_NOARGS,
			.ml_doc = "Get array of node values"
		},

        {
			NULL
		}

 };

 static PyGetSetDef dmiget_node_attributes[] = {
		{
			.name = "name",
			.get = dmiget_node_name,
//			.doc =
		},
		{
			.name = "description",
			.get = dmiget_node_description,
//			.doc =
		},
		{
			.name = "multiple",
			.get = dmiget_node_multiple,
//			.doc =
		},
		{
			.name = "type",
			.get = dmiget_node_type,
//			.doc =
		},
		{
			.name = "handle",
			.get = dmiget_node_handle,
//			.doc =
		},
		{
			.name = "size",
			.get = dmiget_node_size,
//			.doc =
		},
		{
			NULL
		}
 };

 static PyTypeObject dmiget_node_python_type = {

	PyVarObject_HEAD_INIT(NULL, 0)

	.tp_name = "smbios.node",
	.tp_doc = "SMBios node",
	.tp_basicsize = sizeof(pyNode),
	.tp_itemsize = 0,
	.tp_flags = Py_TPFLAGS_HAVE_FINALIZE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,

	.tp_new = dmiget_node_alloc,
	.tp_dealloc = dmiget_node_dealloc,

	.tp_init = dmiget_node_init,
	.tp_finalize = dmiget_node_finalize,

	// .tp_iter =
	// .tp_iternext =

	.tp_str = dmiget_node_str,
	.tp_methods = dmiget_node_methods,
	.tp_getset = dmiget_node_attributes,

	//.tp_getattr = dmiget_node_getattr,

	//.tp_dict =


 };

 static PyMethodDef dmiget_value_methods[] = {

        {
			.ml_name = "next",
			.ml_meth = dmiget_value_next,
			.ml_flags = METH_VARARGS,
			.ml_doc = "Move to next value"
        },

		{
			.ml_name = "empty",
			.ml_meth = dmiget_value_empty,
			.ml_flags = METH_NOARGS,
			.ml_doc = "True if the value is empty"
		},

        {
			NULL
		}

 };

 static PyGetSetDef dmiget_value_attributes[] = {
		{
			.name = "name",
			.get = dmiget_value_name,
//			.doc =
		},
		{
			.name = "description",
			.get = dmiget_value_description,
//			.doc =
		},
		{
			NULL
		}
 };

 static PyTypeObject dmiget_value_python_type  = {

	PyVarObject_HEAD_INIT(NULL, 0)

	.tp_name = "smbios.value",
	.tp_doc = "SMBios Value",
	.tp_basicsize = sizeof(pyValue),
	.tp_itemsize = 0,
	.tp_flags = Py_TPFLAGS_HAVE_FINALIZE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,

	.tp_new = dmiget_value_alloc,
	.tp_dealloc = dmiget_value_dealloc,

	.tp_init = dmiget_value_init,
	.tp_finalize = dmiget_value_finalize,

	// .tp_iter =
	// .tp_iternext =

	.tp_str = dmiget_value_str,
	.tp_methods = dmiget_value_methods,
	.tp_getset = dmiget_value_attributes,

	//.tp_dict =

	//.tp_methods = dmiget_value_methods,

 };

 static PyMethodDef methods[] = {

	{
		"version",
		pydmi_get_module_version,
		METH_NOARGS,
		"Get package version"
	},

	{
		"revision",
		pydmi_get_module_revision,
		METH_NOARGS,
		"Get package revision"

	},

	{
		"nodes",
		pydmi_get_nodes,
		METH_VARARGS,
		"Get array of nodes"

	},

	{
		NULL,
		NULL,
		0,
		NULL
	}

};

static struct PyModuleDef definition = {
	PyModuleDef_HEAD_INIT,
	.m_name = "smbios",							// name of module
	.m_doc = "Get values from SMBIOS table",	// module documentation, may be NUL
	.m_size = -1,								// size of per-interpreter state of the module or -1 if the module keeps state in global variables.
	.m_methods = methods,						// Module methods
	.m_free = (freefunc) cleanup
};

PyMODINIT_FUNC PyInit_smbios(void)
{

	// Initialize node attributes & methods.
	dmiget_node_type_init();
	if (PyType_Ready(&dmiget_node_python_type) < 0)
		return NULL;

	// Initialize value attributes & methods.
	dmiget_value_type_init();
	if (PyType_Ready(&dmiget_value_python_type) < 0)
		return NULL;

    //
    // Initialize module.
    //
    Py_Initialize();

    smbios_module = PyModule_Create(&definition);

    if(!smbios_module)
		return NULL;

	//
	// Create custom types
	//
	Py_INCREF(&dmiget_node_python_type);
    if (PyModule_AddObject(smbios_module, "node", (PyObject *) &dmiget_node_python_type) < 0) {
		Py_DECREF(&dmiget_node_python_type);
		Py_DECREF(smbios_module);
		return smbios_module = NULL;
    }

	Py_INCREF(&dmiget_value_python_type);
    if (PyModule_AddObject(smbios_module, "value", (PyObject *) &dmiget_value_python_type) < 0) {
		Py_DECREF(&dmiget_node_python_type);
		Py_DECREF(&dmiget_value_python_type);
		Py_DECREF(smbios_module);
		return smbios_module = NULL;
    }

    return smbios_module;
}

static void cleanup(PyObject *module) {


}

