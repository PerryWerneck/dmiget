/* SPDX-License-Identifier: LGPL-3.0-or-later */

/*
 * Copyright (C) 2021 Perry Werneck <perry.werneck@gmail.com>
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

 #pragma once

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #ifdef _WIN32
	#include <windows.h>
 #endif // _WIN32

 #include <dmiget/defs.h>
 #include <dmiget/value.h>
 #include <iostream>
 #include <stdint.h>
 #include <stddef.h>
 #include <stdexcept>

 #ifndef _MSC_VER
	 namespace alias DMI = DMIget;
 #endif // _MSC_VER

 namespace DMIget {

 	bool checksum(const uint8_t *buf, size_t len);

	#if defined(BIGENDIAN)

		#define WORD(x)		(uint16_t)	((x)[0] + ((x)[1] << 8))
		#define DWORD(x)	(uint32_t) ((x)[0] + ((x)[1] << 8) + ((x)[2] << 16) + ((x)[3] << 24))

	#else

		#define WORD(x)		(uint16_t)(*(const uint16_t *)(x))
		#define DWORD(x)	(uint32_t)(*(const uint32_t *)(x))
		#define QWORD(x)	(*(const uint64_t *)(x))

	#endif // BIGENDIAN

	struct Header {

		uint8_t type;
		uint8_t length;
		uint16_t handle;
		const uint8_t *data;

		constexpr Header(const uint8_t *d) : type(d[0]), length(d[1]), handle(WORD(d+2)), data(d) {
		}

	};

	struct Value::Record {

		const char *name = nullptr;
		std::shared_ptr<Value>(*value_factory)(const Header &header, const Value::Type *type, const Value::Record *record, uint8_t index);
		uint8_t offset = 0xFF;
		const char *description = nullptr;

	};

	struct Value::Type {
		uint8_t id = 0;
		bool multiple = false;
		const char *name = nullptr;
		const char *description = nullptr;
		const Record * records = nullptr;

		static const Type * find(uint8_t id);
	};


	class File {
	private:
		uint8_t * contents = nullptr;
		size_t length = 0;

	public:
		File(const char *filename, size_t maxlen = 4096);
		~File();

		inline operator bool() const {
			return contents != nullptr;
		}

		inline size_t size() const noexcept {
			return length;
		}

		inline const uint8_t * content() const noexcept {
			return contents;
		}

	};

	/// @brief DMI string.
	class String : public Value {
	private:
		std::string str;

		void set(const char *bp, bool filter);

	public:
		String(const char *bp, bool filter = true);
		String(const Header &header, uint8_t s, bool filter = true);
		virtual ~String();
		std::string as_string() const override;
	};

	/// @brief String value.
	class StringValue : public Value {
	private:
		std::string value;

	public:
		StringValue(const Value::Type *t, const Value::Record *r, const uint8_t i, const String &v) : Value(t,r,i), value(v.as_string()) {
		}

		virtual ~StringValue() {
		}

		std::string as_string() const override {
			return this->value;
		}

	};

	std::shared_ptr<Value> string_factory(const Header &header, const Value::Type *type, const Value::Record *record, uint8_t index);
	std::shared_ptr<Value> firmware_revision_factory(const Header &header, const Value::Type *type, const Value::Record *record, uint8_t index);

 }

 