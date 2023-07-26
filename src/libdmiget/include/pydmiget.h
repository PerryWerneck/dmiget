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

 #pragma once

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #else
	#define PACKAGE_NAME "python3-dmi"
	#define HAVE_GNUC_VISIBILITY 1
 #endif // HAVE_CONFIG_H

 #if defined(_WIN32)

	#define DLL_PRIVATE	extern
	#define DLL_PUBLIC	extern __declspec (dllexport)

 #elif defined (HAVE_GNUC_VISIBILITY)

	#define DLL_PRIVATE		__attribute__((visibility("hidden"))) extern
	#define DLL_PUBLIC		__attribute__((visibility("default"))) extern

 #else

	#error Unable to set visibility attribute

 #endif

 #define PY_SSIZE_T_CLEAN
 #include <Python.h>

 #ifdef __cplusplus
	extern "C" {
 #endif // __cplusplus

 DLL_PRIVATE PyTypeObject pydmi_node_type;
 DLL_PRIVATE PyTypeObject pydmi_value_type;

 DLL_PRIVATE void pydmi_node_type_init();
 DLL_PRIVATE void pydmi_value_type_init();

 DLL_PRIVATE const char * pydmi_check_requires();

 DLL_PRIVATE PyObject * pydmi_get_module_version(PyObject *self, PyObject *args);
 DLL_PRIVATE PyObject * pydmi_get_module_revision(PyObject *self, PyObject *args);

 #ifdef __cplusplus
	}
 #endif // __cplusplus

