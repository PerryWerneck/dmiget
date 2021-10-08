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
 #include <sysinfoapi.h>

 #include <dmiget/table.h>
 #include <cstring>
 #include <cerrno>
 #include <cstring>
 #include <iostream>

 using namespace std;

 namespace DMI {

	Table::Table() {

		// References:
		// https://chen-jiao.github.io/articles/2016/11/09/How-to-access-SMBIOS-in-Windows.html

		// Use GetSystemFirmwareTable
		{
			DWORD smbiosdatasize = GetSystemFirmwareTable('RSMB',0,NULL,0);

#ifdef DEBUG
			cout << "smbiosdatasize=" << smbiosdatasize << endl;
#endif // DEBUG

			if(smbiosdatasize) {
				dmi.len = (uint32_t) smbiosdatasize;
				dmi.contents = new uint8_t[smbiosdatasize+1];
				memset(dmi.contents,0,smbiosdatasize+1);

				DWORD bytesread = GetSystemFirmwareTable('RSMB',0,dmi.contents,smbiosdatasize);

				if(bytesread != smbiosdatasize) {
					cerr << "Invalid data length reading SMBIOS from GetSystemFirmwareTable" << endl;
					delete[] dmi.contents;
					dmi.contents = nullptr;
					dmi.len = 0;
				}
#ifdef DEBUG
				else {
					cout << "Got SMBIOS from GetSystemFirmwareTable" << endl;
				}
#endif // DEBUG
			}
		}

	}

	Table::~Table() {
		if(dmi.contents) {
			delete[] dmi.contents;
		}
	}

 }
