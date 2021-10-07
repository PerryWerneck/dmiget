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

 #include <dmiget/table.h>
 #include <internals.h>
 #include <cstring>
 #include <cerrno>
 #include <cstring>
 #include <iostream>
 #include <functional>

 using namespace std;

 namespace DMI {

	static bool for_each(const uint8_t *buf, uint16_t num, uint32_t len, std::function<bool(const Header &header)> exec) {

		int i = 0;
		const uint8_t * data = buf;
		while ((i < num || !num) && data + 4 <= buf + len) {

			Header h{data};

			//
			// If a short entry is found (less than 4 bytes), not only it
			// is invalid, but we cannot reliably locate the next entry.
			// Also stop at end-of-table marker if so instructed.
			//
			if(h.length < 4 || h.type == 127)
				break;

			i++;

			// Look for the next handle
			const uint8_t *next = data + h.length;

			while ((unsigned long)(next - buf + 1) < len && (next[0] != 0 || next[1] != 0))
				next++;
			next += 2;

			// Make sure the whole structure fits in the table
			if ((unsigned long)(next - buf) > len)
				break;

			// Call
			if(!exec(h)) {
				return false;
			}

			// Get next
			data = next;

		}

		return true;

	}

	bool Table::set(const uint8_t *d, size_t length) {

		if(dmi.contents) {
			delete[] dmi.contents;
		}

		dmi.contents = new uint8_t[length];
		dmi.len = length;
		memcpy(dmi.contents,d,length);

		// Assign vendor for vendor-specific decodes later
		DMI::for_each(dmi.contents, dmi.num, dmi.len,[this](const Header &header) {

			if(header.type == 1 && header.length >= 6) {

				cout << ((unsigned int) header.type) << " " << ((unsigned int) header.length) << endl;

				String vendor(header,header.data[0x04],0);
				String product(header,header.data[0x05],0);

				cout << "Vendor: '" << vendor.as_string() << "' Product: '" << product.as_string() << "'" << endl;

				return false;
			}

			return true;
		});

		return true;
	}

	bool Table::for_each() const {

		return DMI::for_each(dmi.contents, dmi.num, dmi.len,[this](const Header &header) {

			// Fixup a common mistake
			//if(header.type == 34) {
			//	dmi_fixup_type_34(&h, display);
			//}

			const Value::Type * type = Value::Type::find(header.type);

			cout << ((unsigned int) header.type) << " (" << type->description << ") " << ((unsigned int) header.length) << endl;

			if(type->records) {
				cout << "*****************" << endl;
				for(const Value::Record *record = type->records;record->name;record++) {
					cout << type->name << "/" << record->name << " (" << record->description << ")" << endl;

				}
				cout << "*****************" << endl;
			}

			return true;
		});

	}

 }

