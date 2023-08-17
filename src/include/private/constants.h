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
  * @brief Declare constants.
  */

 #pragma once

 #include <smbios/defs.h>
 #include <private/data.h>
 #include <smbios/value.h>

 /*
 namespace SMBios {

	namespace Decoder {

		/// @brief Abstract decoder.
		struct Abstract {
			const Value::Type type;

			constexpr Abstract(const Value::Type t) : type{t} {
			}

			constexpr Abstract() : type{Value::Undefined} {
			}

			virtual std::string as_string(const uint8_t *ptr, const size_t offset) const;
			virtual unsigned int as_uint(const uint8_t *ptr, const size_t offset) const;
			virtual uint64_t as_uint64(const uint8_t *ptr, const size_t offset) const;

#ifndef _MSC_VER
			inline std::string to_string(const uint8_t *ptr, const size_t offset) const {
				return as_string(ptr, offset);
			}
#endif /// !_MSC_VER

		};

	}

	struct Node::Info {
		uint8_t id = 0;
		bool multiple = false;
		const char *name = nullptr;
		const char *description = nullptr;
		const Value::Info * values = nullptr;

		size_t size() const noexcept;

		static const Info * find(uint8_t id);
		static const Info * find(const char *name);
	};


	struct Value::Info {

		const char *name = nullptr;
		const Decoder::Abstract &decoder = Decoder::Abstract{};
		uint8_t offset = 0xFF;
		const char *description = nullptr;

	};

 }
 */

