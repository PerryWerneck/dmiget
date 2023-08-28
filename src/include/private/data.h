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
  * @brief Declare SMBios::Data class
  */

 #pragma once

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <smbios/defs.h>
 #include <memory>
 #include <cstdint>

 #if defined(BIGENDIAN)

	#define WORD(x)		(uint16_t)	((x)[0] + ((x)[1] << 8))
	#define DWORD(x)	(uint32_t) ((x)[0] + ((x)[1] << 8) + ((x)[2] << 16) + ((x)[3] << 24))

 #else

	#define WORD(x)		(uint16_t)(*(const uint16_t *)(x))
	#define DWORD(x)	(uint32_t)(*(const uint32_t *)(x))
	#define QWORD(x)	(*(const uint64_t *)(x))

 #endif // BIGENDIAN

 namespace SMBios {

	class SMBIOS_API Data {
	public:

		enum Type : uint8_t {
			Invalid,
			TYPE1,
			TYPE3
		};

	private:

		struct Dmi {
			/// @brief SMBios type.
			Type type = Invalid;

			/// @brief Length of the SMBIOS Data block.
			size_t length = 0;

			/// @brief Itens on the SMBIOS Data block.
			size_t num = 0;

			uint64_t base = 0;

			uint32_t version = 0;

		} dmi;

		/// @brief Pointer to SMBIOS Data block.
		uint8_t *ptr = nullptr;

	public:

		/// @brief Construct and empty data block.
		constexpr Data() {
		}

		Data(const char *smbios_entry_point, const char *table);
		~Data();

		/// @brief Build data from BIOS.
		static std::shared_ptr<Data> factory();

		/// @brief Build data from filename.
		static std::shared_ptr<Data> factory(const char *filename);

		inline size_t size() const noexcept {
			return dmi.length;
		}

		inline size_t count() const noexcept {
			return dmi.num;
		}

		inline uint32_t version() const noexcept {
			return dmi.version;
		}

		inline uint32_t type() const noexcept {
			return dmi.type;
		}

		const uint8_t * get(int addr) const noexcept {
			return (ptr+addr);
		}

		const uint8_t * operator[](int addr) const noexcept {
			return (ptr+addr);
		}

	};

 }
