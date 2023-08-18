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
		"values",
		pydmi_get_values,
		METH_VARARGS,
		"Get array of values"

	},

	{
		"memsize",
		pydmi_get_memsize,
		METH_VARARGS,
		"Get installed memory"

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

