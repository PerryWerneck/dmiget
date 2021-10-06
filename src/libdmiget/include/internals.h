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

 #include <config.h>
 #include <dmiget/defs.h>
 #include <dmiget/value.h>
 #include <stdint.h>
 #include <stddef.h>
 #include <stdexcept>

 namespace DMI {

 	bool checksum(const uint8_t *buf, size_t len);

	#if defined(BIGENDIAN)

		#define WORD(x)		(uint16_t)	((x)[0] + ((x)[1] << 8))
		#define DWORD(x)	(uint32_t) ((x)[0] + ((x)[1] << 8) + ((x)[2] << 16) + ((x)[3] << 24))
//		#define QWORD(x)	(uint64_t) (DWORD(x), DWORD(x + 4)))

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
	class String : public DMI::Value {
	private:
		std::string str;

	public:
		String(const Header &header, uint8_t s, bool filter = true);
		virtual ~String();
		const std::string as_string() const override;
	};

 }

