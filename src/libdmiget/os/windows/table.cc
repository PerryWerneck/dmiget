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

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <internals.h>
 #include <sysinfoapi.h>

 #include <dmiget/table.h>
 #include <cstring>
 #include <cerrno>
 #include <cstring>
 #include <string>
 #include <iostream>

 using namespace std;

 namespace DMIget {

	Table::Table(const char *filename) {

		File dmifile(filename);

		if(dmifile) {

			if(set(dmifile.content(),dmifile.size())) {
#ifdef DEBUG
				cout << "Got DMI table with " << dmifile.size() << " bytes from " << filename << endl;
#endif // DEBUG
			}

		}

	}

	Table::Table() {

		// References:
		// https://chen-jiao.github.io/articles/2016/11/09/How-to-access-SMBIOS-in-Windows.html

		// Use GetSystemFirmwareTable
		{
			DWORD smbiosdatasize = GetSystemFirmwareTable('RSMB',0,NULL,0);

			if(smbiosdatasize) {

				uint8_t *buffer = new uint8_t[smbiosdatasize+1];

				try {

					DWORD bytesread = GetSystemFirmwareTable('RSMB',0,buffer,smbiosdatasize);

					if(bytesread == smbiosdatasize) {

						#pragma pack(1)
						struct RawSMBIOSData {
							BYTE    Used20CallingMethod;
							BYTE    SMBIOSMajorVersion;
							BYTE    SMBIOSMinorVersion;
							BYTE    DmiRevision;
							DWORD    Length;
							BYTE    SMBIOSTableData[];
						};
						#pragma pack()

						RawSMBIOSData * data = (RawSMBIOSData *) buffer;

						set(data->SMBIOSTableData,data->Length);

					} else {
						cerr << "Invalid response on GetSystemFirmwareTable()" << endl;
					}

				} catch(...) {

					delete[] buffer;
					throw;

				}
			
				delete[] buffer;
			}
		}

	}

	Table::~Table() {
		if(dmi.contents) {
			delete[] dmi.contents;
		}
	}

 }
