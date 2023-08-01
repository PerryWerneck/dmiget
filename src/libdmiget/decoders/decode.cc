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

 /*
 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <internals.h>
 #include <string>
 #include <iostream>
 #include <dmiget/table.h>
 #include <functional>
 #include <cstring>

 using namespace std;

 namespace DMIget {

	bool Table::identify(const uint8_t *entry) {

		static const struct {
			const char *prefix;
			std::function<bool(Table &table, const uint8_t *entry)> exec;
		} formats[] = {

			// SMBIOS3
			{
				"_SM3_",
				[](Table &table, const uint8_t *entry) {

					table.format = SmBios3;

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

					table.dmi.version = (entry[0x07] << 16) + (entry[0x08] << 8) + entry[0x09];

					table.dmi.base = QWORD(entry + 0x10);
					table.dmi.len = DWORD(entry + 0x0C);

					return true;
				}
			},

			// SMBIOS
			{
				"_SM_",
				[](Table &table, const uint8_t *entry) {

					table.format = SmBios;

					// Don't let checksum run beyond the buffer
					if (entry[0x05] > 0x20) {
						throw runtime_error(
									(string{"Entry point length too large ("}
										+ to_string((unsigned int) entry[0x05]),
										+ ", expected"
										+ to_string(0x1FU)
										+ ")").c_str()
						);

					}

					if (!checksum(entry, entry[0x05]) || memcmp(entry + 0x10, "_DMI_", 5) != 0 || !checksum(entry + 0x10, 0x0F)) {
						throw runtime_error("Chksum mismatch");
					}

					uint16_t ver = (entry[0x06] << 8) + entry[0x07];

					// Some BIOS report weird SMBIOS version, fix that up
					switch (ver) {
					case 0x021F:
					case 0x0221:
						ver = 0x0203;
						break;
					case 0x0233:
						ver = 0x0206;
						break;
					}

#ifdef DEBUG
					cout << "SMBIOS " << (ver>>8) << "." << (ver & 0xFF) << endl;
#endif // DEBUG

					table.dmi.base = DWORD(entry + 0x18);
					table.dmi.len = WORD(entry + 0x16);
					table.dmi.num = WORD(entry + 0x1C);
					table.dmi.version = (ver << 8);

					return true;
				}
			},

			// Legacy
			{
				"_SM_",
				[](Table &table, const uint8_t *entry) {

					table.format = Legacy;

					if (!checksum(entry, 0x0F)) {
						throw runtime_error("Checksum mismatch");
					}

#ifdef DEBUG
					cout << "Legacy DMI " << (entry[0x0E] >> 4) << "." << (entry[0x0E] & 0x0F) << endl;
#endif // DEBUG

					table.dmi.base = DWORD(entry + 0x08);
					table.dmi.len = WORD(entry + 0x06);
					table.dmi.num = WORD(entry + 0x0C);
					table.dmi.version = ((entry[0x0E] & 0xF0) << 12) + ((entry[0x0E] & 0x0F) << 8);

					return true;
				}
			}

		};

		for(size_t ix = 0; ix <= (sizeof(formats)/sizeof(formats[0])); ix++) {

			if(memcmp(formats[ix].prefix,entry,strlen(formats[ix].prefix)) == 0) {
#ifdef DEBUG
				cerr << "Got " << formats[ix].prefix << endl;
#endif // DEBUG
				return formats[ix].exec(*this,entry);
			}

		}

#ifdef DEBUG
		cerr << "Can't identify format" << endl;
#endif // DEBUG

		return false;

	}


 }
 */
