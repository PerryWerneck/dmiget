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

 using namespace std;

 namespace DMI {

	Table::Table() {

		File entry_point("/sys/firmware/dmi/tables/smbios_entry_point");

		if(entry_point && identify(entry_point.content())) {

			// Got sysfs
#ifdef DEBUG
			cout << "Got sysfs (base=" << dmi.base << " length=" << dmi.len << ")" << endl;
#endif // DEBUG

			File dmifile("/sys/firmware/dmi/tables/DMI",dmi.len);

			if(dmifile && dmifile.size() == dmi.len) {

				if(set(dmifile.content(),dmifile.size())) {
#ifdef DEBUG
					cout << "Got DMI table from sysfs" << endl;
#endif // DEBUG
					return;
				}

			}

		}

	}

	Table::~Table() {
		if(dmi.contents) {
			delete[] dmi.contents;
		}
	}

 }
