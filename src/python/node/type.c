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
  * @brief Declare python smbios.value type.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <smbios/defs.h>
 #include <private/python.h>

 PyNumberMethods dmiget_node_number_methods = {
 	.nb_bool = dmiget_node_bool,
 	.nb_int = dmiget_node_int,
 };

 PyMethodDef dmiget_node_methods[] = {

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

 PyGetSetDef dmiget_node_attributes[] = {
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

 PyTypeObject dmiget_node_python_type  = {

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

	.tp_as_number = &dmiget_node_number_methods,
	.tp_str = dmiget_node_str,
	.tp_repr = dmiget_node_str,
	.tp_methods = dmiget_node_methods,
	.tp_getset = dmiget_node_attributes,

	//.tp_getattr = dmiget_node_getattr,

	//.tp_dict =

 };

