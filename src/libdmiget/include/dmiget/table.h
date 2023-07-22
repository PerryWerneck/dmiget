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

 #include <dmiget/defs.h>
 #include <stdint.h>
 #include <stddef.h>
 #include <functional>
 #include <string>
 #include <memory>

 #ifdef __cplusplus
 extern "C" {
 #endif

	/// @brief Get DMI value.
	/// @param node Node name.
	/// @param name Value name.
	/// @return String with dmi:///node/name value or empty if not found (release it with free())
	DMIGET_API char * dmi_table_get(const char *node, const char *name);

	/// @brief Get DMI value.
	/// @param url URL dmi:///node/name.
	/// @return String with value or empty if not found (release it with free())
	DMIGET_API char * dmi_table_get_url(const char *url);

 #ifdef __cplusplus
 }
 #endif

 #ifdef __cplusplus
 namespace DMIget {

	class Value;

	class DMIGET_API Table {
	private:

		enum Format : uint8_t {
			Invalid,
			SmBios3,
			SmBios,
			Legacy
		} format = Invalid;

		struct {
			uint64_t base = 0;
			uint32_t len = 0;
			uint16_t num = 0;
			uint32_t version = 0;
			uint8_t *contents = nullptr;
		} dmi;

		/// @brief Identify SMBIOS format.
		bool identify(const uint8_t *entry);

		/// @brief Set DMI table contents.
		bool set(const uint8_t *dmi, size_t length);

	public:
		Table(const char *filename);
		Table();
		~Table();

		inline operator bool() const noexcept {
			return dmi.contents != nullptr;
		}

		bool for_each(std::function<bool(std::shared_ptr<Value> value)> exec) const;

		std::shared_ptr<Value> find(const char *node, const char *name) const;
		std::shared_ptr<Value> find(const char *url) const;
		std::string operator[](const char *url) const;

	};

 }
 #endif // __cplusplus
