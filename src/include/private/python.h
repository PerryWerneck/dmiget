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

 #include <smbios/defs.h>

 #define PY_SSIZE_T_CLEAN
 #include <Python.h>

 #ifdef __cplusplus
 #include <memory>

 using namespace std;
 using namespace SMBios;
 #include <functional>
 #include <smbios/value.h>

 extern "C" {
 #endif // __cplusplus

 struct pyNodePrivate;

 typedef struct {
        PyObject_HEAD
        struct pyNodePrivate *pvt;
 } pyNode;

 struct pyValuePrivate;

 typedef struct {
        PyObject_HEAD
        struct pyValuePrivate *pvt;
 } pyValue;

 extern SMBIOS_PRIVATE PyObject * smbios_module;

 SMBIOS_PRIVATE void dmiget_node_type_init();
 SMBIOS_PRIVATE void dmiget_value_type_init();

 SMBIOS_PRIVATE PyObject * pydmi_get_module_version(PyObject *, PyObject *);
 SMBIOS_PRIVATE PyObject * pydmi_get_module_revision(PyObject *, PyObject *);

 SMBIOS_PRIVATE int dmiget_node_init(PyObject *self, PyObject *args, PyObject *);
 SMBIOS_PRIVATE void dmiget_node_finalize(PyObject *self);
 SMBIOS_PRIVATE PyObject * dmiget_node_alloc(PyTypeObject *type, PyObject *, PyObject *);
 SMBIOS_PRIVATE void dmiget_node_dealloc(PyObject * self);

 SMBIOS_PRIVATE int dmiget_value_init(PyObject *self, PyObject *args, PyObject *);
 SMBIOS_PRIVATE void dmiget_value_finalize(PyObject *self);
 SMBIOS_PRIVATE PyObject * dmiget_value_alloc(PyTypeObject *type, PyObject *, PyObject *);
 SMBIOS_PRIVATE void dmiget_value_dealloc(PyObject * self);

 //
 // smbios.value object
 //
 extern SMBIOS_PRIVATE PyMethodDef dmiget_value_methods[];
 extern SMBIOS_PRIVATE PyGetSetDef dmiget_value_attributes[];
 extern SMBIOS_PRIVATE PyTypeObject dmiget_value_python_type;

 SMBIOS_PRIVATE int dmiget_value_bool(PyObject *self);
 SMBIOS_PRIVATE PyObject * dmiget_value_int(PyObject *self);

 SMBIOS_PRIVATE PyObject * dmiget_value_getattr(PyObject *, char *);
 SMBIOS_PRIVATE PyObject * dmiget_value_str(PyObject *self);
 SMBIOS_PRIVATE PyObject * dmiget_value_name(PyObject *self, void *);
 SMBIOS_PRIVATE PyObject * dmiget_value_description(PyObject *self, void *);
 SMBIOS_PRIVATE PyObject * dmiget_value_next(PyObject *self, PyObject *args);
 SMBIOS_PRIVATE PyObject * dmiget_value_empty(PyObject *self, PyObject *args);

 //
 // smbios.node object
 //
 extern SMBIOS_PRIVATE PyMethodDef dmiget_node_methods[];
 extern SMBIOS_PRIVATE PyGetSetDef dmiget_node_attributes[];
 extern SMBIOS_PRIVATE PyTypeObject dmiget_node_python_type;

 SMBIOS_PRIVATE int dmiget_node_bool(PyObject *self);
 SMBIOS_PRIVATE PyObject * dmiget_node_int(PyObject *self);

 SMBIOS_PRIVATE PyObject * dmiget_node_str(PyObject *self);
 SMBIOS_PRIVATE PyObject * dmiget_node_next(PyObject *self, PyObject *args);
 SMBIOS_PRIVATE PyObject * dmiget_node_value(PyObject *self, PyObject *args);
 SMBIOS_PRIVATE PyObject * dmiget_node_values(PyObject *self, PyObject *args);
 SMBIOS_PRIVATE PyObject * dmiget_node_name(PyObject *self, void *);
 SMBIOS_PRIVATE PyObject * dmiget_node_description(PyObject *self, void *);
 SMBIOS_PRIVATE PyObject * dmiget_node_multiple(PyObject *self, void *);
 SMBIOS_PRIVATE PyObject * dmiget_node_type(PyObject *self, void *);
 SMBIOS_PRIVATE PyObject * dmiget_node_handle(PyObject *self, void *);
 SMBIOS_PRIVATE PyObject * dmiget_node_size(PyObject *self, void *);
 SMBIOS_PRIVATE PyObject * dmiget_node_empty(PyObject *self, PyObject *args);

 /// @brief Build node array.
 SMBIOS_PRIVATE PyObject * pydmi_get_nodes(PyObject *self, PyObject *args);
 SMBIOS_PRIVATE PyObject * pydmi_get_values(PyObject *self, PyObject *args);

 SMBIOS_PRIVATE PyObject * pydmi_get_memsize(PyObject *self, PyObject *args);

 /// @brief Build Python objet by typename.
 /// @param name The nome of python object to build;
 SMBIOS_PRIVATE PyObject * PyObjectByName(const char *name);


 #ifdef __cplusplus
 SMBIOS_PRIVATE PyObject * dmiget_set_value(PyObject *self, std::shared_ptr<SMBios::Value> value);

 }
 #endif // __cplusplus
