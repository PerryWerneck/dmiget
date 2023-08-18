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

 PyNumberMethods dmiget_value_number_methods = {
 	.nb_bool = dmiget_value_bool,
 	.nb_int = dmiget_value_int,
 };

 PyMethodDef dmiget_value_methods[] = {

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

 PyGetSetDef dmiget_value_attributes[] = {
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

 PyTypeObject dmiget_value_python_type  = {

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
	.tp_as_number = &dmiget_value_number_methods,

	// .tp_iter =
	// .tp_iternext =

	.tp_str = dmiget_value_str,
	.tp_repr = dmiget_value_str,
	.tp_methods = dmiget_value_methods,
	.tp_getset = dmiget_value_attributes,

	//.tp_dict =

 };

