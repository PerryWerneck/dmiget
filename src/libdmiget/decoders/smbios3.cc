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

 #include <config.h>
 #include <internals.h>
 #include <string>
 #include <iostream>
 #include <dmiget/table.h>

 using namespace std;

 namespace DMI {

 	void Table::smbios3_decode(const uint8_t *entry) {

		this->format = SmBios3;

		if (entry[0x06] > 0x20) {
			throw runtime_error(
						(string{"Entry point length too large ("}
							+ to_string((unsigned int) entry[0x06]),
							+ ", expected"
							+ to_string(0x18U)
							+ ")").c_str()
			);
		}

		if(!checksum(entry, entry[0x06])) {
			throw runtime_error("Chksum mismatch");
		}

#ifdef DEBUG
		cout << "SMBIOS " << ((unsigned int) entry[7]) << "." << ((unsigned int) entry[8]) << "." << ((unsigned int) entry[9]) << endl;
#endif // DEBUG

		dmi.version = (entry[0x07] << 16) + (entry[0x08] << 8) + entry[0x09];

		dmi.base = QWORD(entry + 0x10);
		dmi.len = DWORD(entry + 0x0C);

 	}

 }
