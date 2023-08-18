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
  * @brief Implements Memory size object.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <private/data.h>
 #include <smbios/node.h>
 #include <smbios/value.h>
 #include <smbios/memsize.h>
 #include <sstream>
 #include <iomanip>

 namespace SMBios {

	MemSize::MemSize() : value{0LL} {

		Node::for_each(17,[this](const Node &node){
			value += node["size"]->as_uint64();
			return false;
		});


	}

	bool MemSize::empty() const {
		return value;
	}

	const char *MemSize::name() const noexcept {
		return "memsize";
	}

	const char *MemSize::description() const noexcept {
		return "System memory";
	}

	std::string MemSize::as_string() const {
		return as_string(2);
	}

	std::string MemSize::as_string(int precision) const {

		static const char * unit_names[] = { "Bytes", "KB", "MB", "GB", "TB" };

		static const double step{1024.0};

		double multiplier{step};
		double selected{1};
		double val = (double) this->value;

		const char *name = unit_names[0];
		for(size_t ix = 1; ix < (sizeof(unit_names) / sizeof(unit_names[0]));ix++) {

			if(value >= multiplier) {
				selected = multiplier;
				name = unit_names[ix];
			}

			multiplier *= step;

		}

		std::stringstream stream;

		stream
			<< std::fixed << std::setprecision(precision) << (val/selected);

		if(name && *name) {
			stream << " " << name;
		}

		return stream.str();

	}

 }
