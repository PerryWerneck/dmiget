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

	bool checksum(const uint8_t *buf, size_t len) {
		uint8_t sum = 0;

		for(size_t a = 0; a < len; a++)
			sum += buf[a];

		return (sum == 0);
	}

	void dmi_table(uint64_t base, uint32_t len, uint16_t num, uint32_t version, const uint8_t *buffer) {

	}

 	bool Table::smbios3_decode(const uint8_t *entry, const uint8_t *buffer) {

		if (buffer[0x06] > 0x20) {
			throw runtime_error(
						(string{"Entry point length too large ("}
							+ to_string((unsigned int) buffer[0x06]),
							+ ", expected"
							+ to_string(0x18U)
							+ ")").c_str()
			);
		}

		if(!checksum(buffer, buffer[0x06])) {
			throw runtime_error("Chksum mismatch");
		}

		this->version = (buffer[0x07] << 16) + (buffer[0x08] << 8) + buffer[0x09];

#ifdef DEBUG
		cout << "SMBIOS " << ((unsigned int) buffer[7]) << "." << ((unsigned int) buffer[8]) << "." << ((unsigned int) buffer[9]) << endl;
#endif // DEBUG

		dmi_table(
			QWORD(buffer + 0x10),
			DWORD(buffer + 0x0C),
			0,
			this->version,
			buffer
		);

 	}

 }
