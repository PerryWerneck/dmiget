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
  * @brief Declare SMBios node.
  */

 #pragma once

 #include <smbios/defs.h>
 #include <smbios/value.h>
 #include <iostream>
 #include <iterator>
 #include <memory>
 #include <functional>
 #include <cstdint>
 #include <vector>

 namespace SMBios {

 	class SMBIOS_API Node {
	public:

		struct Header{
			uint8_t type = 0;
			uint8_t length = 0;
			uint16_t handle = 0;

			static const Header & get(std::shared_ptr<Data> data, const int offset);

		};

		/// @brief Construct an empty node.
		Node();

		/// @brief Construct node from id.
		/// @param type SMBIos rype.
		Node(uint8_t type, int index = 0);

		/// @brief Construct node.
		/// @param name	Node name (empty for the first one)
		/// @param index Node index.
		Node(const char *name, int index = 0);

		/// @brief Construct node reading SMBios from dump file.
		/// @param SMBios dump file (empty for the system's table).
		/// @param name	Node name (empty for the first one)
		/// @param index Node index.
		static Node factory(const char *filename, const char *name = "", int index = 0);

		Node & operator=(const uint8_t type);
		Node & operator=(const char *name);

		operator bool() const;

		Node & rewind();
		Node & next();
		Node & next(uint8_t type, size_t count = 1);
		Node & next(const char *name, size_t count = 1);

		const char *name() const noexcept;
		const char *description() const noexcept;

		bool multiple() const noexcept;

		inline short type() const noexcept {
			return (short) header.type;
		}

		inline size_t size() const noexcept {
			return (size_t) header.length;
		}

		inline uint16_t handle() const noexcept {
			return header.handle;
		}

		std::shared_ptr<Value> operator[](size_t index) const;
		std::shared_ptr<Value> operator[](const char *name) const;

		/// @brief Find value from path.
		std::shared_ptr<Value> find(const char *path) const;

		Node operator++(int);
		Node & operator++();

		static bool for_each(const std::function<bool(const Node &node)> &call);
		static bool for_each(const std::function<bool(const Node &node, size_t index)> &call);
		static bool for_each(uint8_t type,const std::function<bool(const Node &node)> &call);
		static bool for_each(const char *name,const std::function<bool(const Node &node)> &call);
		static bool for_each(const std::function<bool(const Node &node, const size_t index, const Value &v)> &call);

		bool for_each(const std::function<bool(const Value &v)> &call) const;
		bool for_each(const std::function<bool(std::shared_ptr<Value> value)> &call) const;

		Value::Iterator begin();
		Value::Iterator end();

		class Iterator;

	private:

		/// @brief Private decoder for this node.
		std::shared_ptr<Data> data;
		int offset;
		size_t index = 0;
		Header header;
		const Decoder::Type *decoder = nullptr;

		Node & setup(int offset = 0);

		Node(std::shared_ptr<Data> data, const int offset = 0);

 	};

 	inline Node begin() {
		return Node{};
 	}

 }

