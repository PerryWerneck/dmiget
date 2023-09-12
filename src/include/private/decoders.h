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

 #pragma once

 #include <smbios/defs.h>
 #include <private/data.h>
 #include <smbios/value.h>
 #include <smbios/node.h>

 namespace SMBios {

 	namespace Decoder {

		class Value : public SMBios::Value {
		private:
			const Decoder::Type &type;
			std::shared_ptr<Data> data;
			int offset;
			size_t item;

		protected:
			std::shared_ptr<SMBios::Value> clone() const override;

		public:
			Value(const Decoder::Type &type, std::shared_ptr<Data> data, int offset, size_t item);
			virtual ~Value();
			static std::shared_ptr<SMBios::Value> factory(const Decoder::Type &type, std::shared_ptr<Data> data, int offset, size_t item);

			const char *name() const noexcept override;
			const char *description() const noexcept override;
			std::string as_string() const override;
			bool empty() const override;
			uint64_t as_uint64() const override;
			unsigned int as_uint() const override;
			SMBios::Value & next() override;

		};

		struct Worker {
			virtual std::string as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const;
			virtual unsigned int as_uint(const Node::Header &header, const uint8_t *ptr, const size_t offset) const;
			virtual uint64_t as_uint64(const Node::Header &header, const uint8_t *ptr, const size_t offset) const;
		};

		struct String : public Worker {
			std::string as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
		};

		struct UInt8 : public Worker {
			unsigned int as_uint(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
			std::string as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
		};

		struct UInt16 : public Worker {
			unsigned int as_uint(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
			std::string as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
		};

		/// 0x + 8 hexadecimal digits.
		struct Hex16 : public UInt16 {
			std::string as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
		};

		/// @brief Get an uint64_t value, format string in bytes.
		struct LengthInBytes : public Worker {
			std::string as_string(const Node::Header &header, const uint8_t *ptr, const size_t offset) const override;
		};

		struct Item {

			const char *name = nullptr;
			const Worker &worker = Worker{};
			uint8_t offset = 0xFF;
			const char *description = nullptr;

		};

		struct Type {

			uint8_t type = 0;
			bool multiple = false;
			const char *name = nullptr;
			const char *description = nullptr;
			const Item *itens = nullptr;

			std::shared_ptr<SMBios::Value> (*factory)(const Decoder::Type &type, std::shared_ptr<Data> data, int offset, size_t item) = Value::factory;

			constexpr Type(uint8_t t, bool m, const char *n, const char *d, const Item *i)
				: type{t},multiple{m},name{n},description{d},itens{i} {
			}

		};

		const Decoder::Type * get(const uint8_t type);
		const Decoder::Type * get(const char *name);
		const Decoder::Type * get(std::shared_ptr<Data> data, const int offset);

 	};

 }
