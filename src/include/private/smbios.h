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
  * @brief Declares SMBiosData blass
  */

 #pragma once

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <smbios/defs.h>
 #include <memory>
 #include <cstdint>

 namespace SMBios {

	class SMBIOS_API Data {
	public:

		enum Type : uint8_t {
			Invalid,
			TYPE1,
			TYPE3
		};

	private:

		struct {

			/// @brief SMBios type;
			Type type = Invalid;

		} options;

		/// @brief Pointer to SMBIOS Data block.
		uint8_t *ptr = nullptr;

		/// @brief Length of the SMBIOS Data block.
		size_t length = 0;

	public:

		Data();
		Data(uint8_t *ptr, size_t length);
		~Data();

		/// @brief Build data from BIOS.
		static std::shared_ptr<Data> factory();

		/// @brief Build data from filename.
		static std::shared_ptr<Data> factory(const char *filename);

		inline size_t size() const noexcept {
			return length;
		}

		const uint8_t * operator[](int addr) const noexcept {
			return (ptr+addr);
		}

	};
 }
