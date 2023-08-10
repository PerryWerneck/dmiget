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
 #include <private/smbios.h>
 #include <smbios/value.h>
 #include <smbios/node.h>

 namespace SMBios {

	struct Node::Info {
		uint8_t id = 0;
		bool multiple = false;
		const char *name = nullptr;
		const char *description = nullptr;
		const Value::Info * values = nullptr;

		size_t size() const noexcept;

		static const Info * find(uint8_t id);
	};

	namespace Decoder {

		/// @brief Abstract decoder.
		struct Abstract {
			const Value::Type type;

			constexpr Abstract(const Value::Type t) : type{t} {
			}

			constexpr Abstract() : type{Value::Invalid} {
			}

			virtual std::string as_string(const uint8_t *ptr, const size_t offset) const;

			inline std::string to_string(const uint8_t *ptr, const size_t offset) const {
				return as_string(ptr, offset);
			}

		};

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

			virtual uint16_t as_int16(const uint8_t *ptr, const size_t offset) const;

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

	}

	struct Value::Info {

		const char *name = nullptr;
		const Decoder::Abstract &decoder = Decoder::Abstract{};
		uint8_t offset = 0xFF;
		const char *description = nullptr;

	};

 }

