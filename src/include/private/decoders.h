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

/*
 * Based on dmidecode
 *
 * Copyright (C) 2000-2002 Alan Cox <alan@redhat.com>
 * Copyright (C) 2002-2020 Jean Delvare <jdelvare@suse.de>
 *
 */

 #include <smbios/defs.h>
 #include <private/constants.h>

 /**
  * @brief Decoders definitions.
  */

 namespace SMBios {

#ifdef BIGENDIAN
	struct u64 {
		uint32_t h = 0;
		uint32_t l = 0;
		std::string as_memory_size(int shift = 1) const;
	};
#else
	struct u64 {
		uint32_t l = 0;
		uint32_t h = 0;
		std::string as_memory_size(int shift = 1) const;
	};
#endif

	namespace Decoder {

		/// @brief Decode to string by index.
		struct StringIndex : public Abstract {

			constexpr StringIndex() : Abstract{Value::String} {
			}

			std::string as_string(const uint8_t *ptr, const size_t index) const override;
		};

		struct String : public Abstract {

			constexpr String() : Abstract{Value::String} {
			}

			std::string as_string(const uint8_t *ptr, const size_t index) const override;
		};

		/// @brief Decode firmware revision.
		struct FirmwareRevision : public Abstract {

			constexpr FirmwareRevision() : Abstract{Value::Integer} {
			}

			std::string as_string(const uint8_t *ptr, const size_t offset) const override;
		};

		struct UInt16 : public Abstract {

			constexpr UInt16() : Abstract{Value::Integer} {
			}

			unsigned int as_uint(const uint8_t *ptr, const size_t offset) const override;
			std::string as_string(const uint8_t *ptr, const size_t offset) const override;

		};

		struct ProcessorType : public UInt16 {

			constexpr ProcessorType() = default;

			unsigned int as_uint(const uint8_t *ptr, const size_t offset) const override;
			std::string as_string(const uint8_t *ptr, const size_t offset) const override;
		};

		struct MemoryDeviceWidth : public UInt16 {

			constexpr MemoryDeviceWidth() = default;

			std::string as_string(const uint8_t *ptr, const size_t offset) const override;
		};

		struct MemoryDeviceFormFactor : public String {

			constexpr MemoryDeviceFormFactor() = default;

			std::string as_string(const uint8_t *ptr, const size_t offset) const override;
		};

		struct MemorySize : public String {

			constexpr MemorySize() = default;

			std::string as_string(const uint8_t *ptr, const size_t offset) const override;
		};

	}

 }
