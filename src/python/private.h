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
  * @brief Brief description of this source.
  */

 #pragma once

 #include <dmiget/defs.h>
 #include <dmiget/table.h>

 #define PY_SSIZE_T_CLEAN
 #include <Python.h>

 #ifdef __cplusplus
 using namespace std;
 namespace DMI = DMIget;
 #include <functional>

 extern "C" {
 #endif // __cplusplus

 DMIGET_PRIVATE PyTypeObject dmiget_node_type;
 DMIGET_PRIVATE PyTypeObject dmiget_value_type;

 DMIGET_PRIVATE void dmiget_node_type_init();
 DMIGET_PRIVATE void dmiget_value_type_init();

 DMIGET_PRIVATE PyObject * pydmi_get_module_version(PyObject *, PyObject *);
 DMIGET_PRIVATE PyObject * pydmi_get_module_revision(PyObject *, PyObject *);

 #ifdef __cplusplus
 DMIGET_PRIVATE PyObject * dmiget_call(PyObject *self, const std::function<std::string (const DMI::Table &dmi)> &worker) noexcept;

	}
 #endif // __cplusplus
