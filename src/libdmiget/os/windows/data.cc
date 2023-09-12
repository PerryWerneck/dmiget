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
  * @brief SMBIos data methods for windows.
  */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <windows.h>

 #include <private/data.h>
 #include <stdexcept>
 #include <system_error>

 #include <iostream>

 using namespace std;

 namespace SMBios {

	std::shared_ptr<Data> Data::factory() {

		auto smbios_data = make_shared<Data>();

		// References:
		// https://chen-jiao.github.io/articles/2016/11/09/How-to-access-SMBIOS-in-Windows.html
		// Use GetSystemFirmwareTable

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
						DWORD   Length;
						BYTE    SMBIOSTableData[];
					};
					#pragma pack()

					RawSMBIOSData * data = (RawSMBIOSData *) buffer;

					smbios_data->dmi.version = (((uint16_t) data->SMBIOSMajorVersion) << 8) | ((uint16_t) data->SMBIOSMinorVersion);
					smbios_data->dmi.length = data->Length;
					smbios_data->ptr = new uint8_t[smbios_data->dmi.length+1];
					smbios_data->ptr[smbios_data->dmi.length] = 0;
					memcpy(smbios_data->ptr,data->SMBIOSTableData,smbios_data->dmi.length);

				} else {
					cerr << "Invalid response on GetSystemFirmwareTable()" << endl;
				}

			} catch(...) {

				delete[] buffer;
				throw;

			}

			delete[] buffer;
		}

		return smbios_data;
	}

	/*
	Data::Data() {


	}
	*/

	Data::~Data() {
		delete[] ptr;
	}

 }
