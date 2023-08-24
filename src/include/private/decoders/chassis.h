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
  * @brief Declare chassis decoders.
  */

 #pragma once

 #include <smbios/defs.h>
 #include <private/decoders.h>

 namespace SMBios {

 	namespace Decoder {

		struct ChassisState : public UInt8 {
			std::string as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
		};

		struct ChassisLock : public UInt8 {
			unsigned int as_uint(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
			std::string as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
		};

		struct ChassisType : public Worker {
			unsigned int as_uint(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
			std::string as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
		};

		struct ChassisSecurityStatus : public UInt8 {
			std::string as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
		};

		struct ChassisOEMInformation : public Hex16 {
			unsigned int as_uint(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
			std::string as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
		};

		struct ChassisHeight : public UInt8 {
			unsigned int as_uint(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
			std::string as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
		};

 	}

 }


