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

 /**
  * @brief Decoders definitions.
  */

 #include <smbios/defs.h>
 #include <private/data.h>
 #include <smbios/value.h>

 namespace SMBios {

	namespace Decoder {

		struct Abstract {

			const char *name = nullptr;			///< @brief The value name.
			uint8_t offset = 0xFF;				///< @brief The offset for value identifier.
			const char *description = nullptr;	///< @brief The value description.

			constexpr Abstract(const char *n = nullptr, const char *d = nullptr, uint8_t o = 0) : name{n},offset{o},description{d} {
			}

			virtual std::string as_string(const uint8_t *ptr, const size_t offset) const;
			virtual unsigned int as_uint(const uint8_t *ptr, const size_t offset) const;
			virtual uint64_t as_uint64(const uint8_t *ptr, const size_t offset) const;
		};

		/// @brief Construct SMBios value from decoder & header offset
		/// @param data Pointer to SMBios data.
		/// @param offset Offset to the beggining of SMBios structure.
		/// @param decoder Pointer to the decoder item.
		/// @param item The decoder item.
		std::shared_ptr<SMBios::Value> ValueFactory(std::shared_ptr<Data> data, size_t offset, const Decoder::Abstract *decoder, size_t item = 0);

		struct String : public Abstract {

			constexpr String(const char *name, const char *description, uint8_t offset = 0) : Abstract{name,description,offset} {
			}

			std::string as_string(const uint8_t *ptr, const size_t offset) const override;
			unsigned int as_uint(const uint8_t *ptr, const size_t offset) const override;
			uint64_t as_uint64(const uint8_t *ptr, const size_t offset) const override;

		};


	};

 }

 /*
 namespace SMBios {

	struct u64 {
#ifdef BIGENDIAN
		uint32_t h = 0;
		uint32_t l = 0;
#else
		uint32_t l = 0;
		uint32_t h = 0;
#endif
		void decode_memory_size(unsigned long &capacity, int &i) const;
		std::string as_memory_size_string(int shift = 1) const;
		uint64_t as_memory_size_bytes(int shift = 1) const;

	};

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

			constexpr FirmwareRevision() : Abstract{Value::Unsigned} {
			}

			std::string as_string(const uint8_t *ptr, const size_t offset) const override;
		};

		struct UInt16 : public Abstract {

			constexpr UInt16() : Abstract{Value::Unsigned} {
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
			uint64_t as_uint64(const uint8_t *ptr, const size_t offset) const override;

		};

		struct TemperatureProbeValue : public Abstract {

			constexpr TemperatureProbeValue() = default;

			std::string as_string(const uint8_t *ptr, const size_t offset) const override;
			uint64_t as_uint64(const uint8_t *ptr, const size_t offset) const override;

		};

	}

 }
 */
