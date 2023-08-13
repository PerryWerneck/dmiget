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
  * @brief Declare SMBios abstract object.
  */

 #pragma once
 #include <smbios/defs.h>
 #include <string>
 #include <memory>

 namespace SMBios {

	class SMBIOS_API Object {
	protected:
		std::shared_ptr<Data> data;
		int offset = -1;

		Object(const int offset = -1);
		Object(const char *filename, const int offset = -1);

		Object(std::shared_ptr<Data> d, const int o = -1) : data{d}, offset{o} {
		}

	public:
		virtual ~Object();

		virtual const char *name() const noexcept = 0;
		virtual const char *description() const noexcept = 0;

		virtual operator bool() const;

	};

 }
