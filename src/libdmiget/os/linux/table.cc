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

 #include "private.h"
 #include <cstring>
 #include <cerrno>
 #include <system_error>

 using namespace std;

 namespace DMI {

	static const Type types[] = {
		{
			0,0,
			"BIOS",
			"BIOS Information",
			(const Entry []) {
				{
					0,
					nullptr,
					"Vendor"
				},
				{
					1,
					nullptr,
					"Version"
				},
				{
					2,
					"rdate",
					"Release Date"
				},
				{
					3,
					"brev",
					"Bios Revision"
				},

				ENTRY_LIST_TERMINATOR

			}
		},

		{
			1,0,
			nullptr,
			"System",
			(const Entry []) {
				{
					0,
					"Manufacturer",
					nullptr
				},
				{
					1,
					"product",
					"Product Name"
				},
				{
					2,
					"Version",
					nullptr
				},
				{
					3,
					"serial",
					"Serial Number"
				},

				ENTRY_LIST_TERMINATOR

			}
		},
		/*
		{
			2,
			nullptr,
			"Base Board"
		},
		*/
		{
			3,0,
			"Chassis",
			"Chassis Information",
			(const Entry []) {
				{
					0,
					"Manufacturer",
					nullptr
				},

				{
					1,
					"Version",
					nullptr
				},

				{
					2,
					"Serial",
					"Serial Number"
				},

				{
					3,
					"atag",
					"Asset Tag"
				},

				ENTRY_LIST_TERMINATOR
			}
		},
		/*
		{
			4,
			nullptr,
			"Processor"
		},
		{
			5,
			nullptr,
			"Memory Controller"
		},
		{
			6,
			nullptr,
			"Memory Module"
		},
		{
			7,
			nullptr,
			"Cache"
		},
		{
			8,
			nullptr,
			"Port Connector"
		},
		{
			9,
			nullptr,
			"System Slots"
		},
		{
			10,
			nullptr,
			"On Board Devices"
		},
		{
			11,
			nullptr,
			"OEM Strings"
		},
		{
			12,
			"sysconf",
			"System Configuration Options"
		},
		{
			13,
			nullptr,
			"BIOS Language"
		},
		{
			14,
			nullptr,
			"Group Associations"
		},
		{
			15,
			"syslog",
			"System Event Log"
		},
		{
			16,
			nullptr,
			"Physical Memory Array"
		},
		{
			17,
			nullptr,
			"Memory Device"
		},
		{
			18,
			nullptr,
			"32-bit Memory Error"
		},
		{
			19,
			nullptr,
			"Memory Array Mapped Address"
		},
		{
			20,
			nullptr,
			"Memory Device Mapped Address"
		},
		{
			21,
			nullptr,
			"Built-in Pointing Device"
		},
		{
			22,
			nullptr,
			"Portable Battery"
		},
		{
			23,
			nullptr,
			"System Reset"
		},
		{
			24,
			nullptr,
			"Hardware Security"
		},
		{
			25,
			nullptr,
			"System Power Controls"
		},
		{
			26,
			nullptr,
			"Voltage Probe"
		},
		{
			27,
			nullptr,
			"Cooling Device"
		},
		{
			28,
			nullptr,
			"Temperature Probe"
		},
		{
			29,
			nullptr,
			"Electrical Current Probe"
		},
		{
			30,
			nullptr,
			"Out-of-band Remote Access"
		},
		{
			31,
			nullptr,
			"Boot Integrity Services"
		},
		{
			32,
			"sysboot",
			"System Boot"
		},
		{
			33,
			nullptr,
			"64-bit Memory Error"
		},
		{
			34,
			nullptr,
			"Management Device"
		},
		{
			35,
			nullptr,
			"Management Device Component"
		},
		{
			36,
			nullptr,
			"Management Device Threshold Data"
		},
		{
			37,
			nullptr,
			"Memory Channel"
		},
		{
			38,
			"ipmi",
			"IPMI Device"
		},
		{
			39,
			nullptr,
			"Power Supply"
		},
		{
			40,
			nullptr,
			"Additional Information"
		},
		{
			41,
			nullptr,
			"Onboard Device"
		},
		{
			42,
			nullptr,
			"Management Controller Host Interface"
		},
		{
			43,
			"TPM",
			"TPM Device"
		},
		*/

	};


	const Type * Type::find(const string &name) {

		for(size_t ix = 0; ix < (sizeof(types)/sizeof(types[0]));ix++) {

			if(types[ix].name && !strcasecmp(types[ix].name,name.c_str())) {
				return types+ix;
			}

			if(types[ix].description && !strcasecmp(types[ix].description,name.c_str())) {
				return types+ix;
			}

		}

		throw system_error(ENOENT,system_category(),string{"Can't find type '"} + name + "'");

	}


 }

