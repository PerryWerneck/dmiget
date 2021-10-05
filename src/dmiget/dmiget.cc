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

 #include <iostream>
 #include <dmiget/value.h>
 #include <iostream>

 using namespace std;

 int main(int argc, const char **argv) {

#ifdef DEBUG

	/*
	cout << DMI::Value("dmi://bios/vendor").as_string() << endl;
	cout << DMI::Value("dmi://bios/version").as_string() << endl;
	cout << DMI::Value("dmi://bios/rdate").as_string() << endl;
	*/

	/*
	{ DMI_CHASSIS_INFO,     DMI_CHASSIS_INFO_ASSET_TAG_OFFSET               }, = 03
	{ DMI_SYSTEM_INFO,      DMI_SYSTEM_INFO_SERIAL_NUMBER_OFFSET    		}, = 01
	{ DMI_CHASSIS_INFO,     DMI_CHASSIS_INFO_SERIAL_NUMBER_OFFSET   		}  = 03

	"chassis/Asset Tag"
	"system/Asset Tag"
	"chassis/Serial Number"
	*/

	/*
	cout << DMI::Value("dmi://chassis/manufacturer").as_string() << endl;
	cout << DMI::Value("dmi://chassis/version").as_string() << endl;
	cout << DMI::Value("dmi://chassis/serial").as_string() << endl;
	cout << DMI::Value("dmi://chassis/atag").as_string() << endl;
	*/

	cout << DMI::Value("dmi://system/manufacturer").as_string() << endl;
	cout << DMI::Value("dmi://system/product").as_string() << endl;
	cout << DMI::Value("dmi://system/version").as_string() << endl;
	cout << DMI::Value("dmi://system/serial").as_string() << endl;

#endif // DEBUG

	for(int arg = 1; arg < argc; arg++) {
 		cout << DMI::Value(argv[arg]).as_string() << endl;
	}


	return 0;
 }
