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

 namespace DMI {

	static const Value::Type types[] = {

		{
			0,
			"bios",
			"BIOS Information"
		},
		{
			1,
			"system",
			"System"
		},
		{
			2,
			"baseboard",
			"Base Board"
		},
		{
			3,
			"Chassis",
			"Chassis Information",
		},
		{
			4,
			"processor",
			"Processor"
		},
		{
			5,
			"mcntrl",
			"Memory Controller"
		},
		{
			6,
			"mmodule",
			"Memory Module"
		},
		{
			7,
			"cache",
			"Cache"
		},
		{
			8,
			"pconn",
			"Port Connector"
		},
		{
			9,
			"slots",
			"System Slots"
		},
		{
			10,
			"boarddevices",
			"On Board Devices"
		},
		{
			11,
			"oemstrings",
			"OEM Strings"
		},
		{
			12,
			"sysconf",
			"System Configuration Options"
		},
		{
			13,
			"blanguage",
			"BIOS Language"
		},
		{
			14,
			"gassoc",
			"Group Associations"
		},
		{
			15,
			"syslog",
			"System Event Log"
		},
		{
			16,
			"pma",
			"Physical Memory Array"
		},
		{
			17,
			"mdev",
			"Memory Device"
		},
		{
			18,
			"32bme",
			"32-bit Memory Error"
		},
		{
			19,
			"mama",
			"Memory Array Mapped Address"
		},
		{
			20,
			"mdma",
			"Memory Device Mapped Address"
		},
		{
			21,
			"pointingdevice",
			"Built-in Pointing Device"
		},
		{
			22,
			"battery",
			"Portable Battery"
		},
		{
			23,
			"sysreset",
			"System Reset"
		},
		{
			24,
			"hwsecurity",
			"Hardware Security"
		},
		{
			25,
			"syspowercntrl",
			"System Power Controls"
		},
		{
			26,
			"vprobe",
			"Voltage Probe"
		},
		{
			27,
			"cooling",
			"Cooling Device"
		},
		{
			28,
			"temperature",
			"Temperature Probe"
		},
		{
			29,
			"electricalcurrent",
			"Electrical Current Probe"
		},
		{
			30,
			"ora",
			"Out-of-band Remote Access"
		},
		{
			31,
			"bis",
			"Boot Integrity Services"
		},
		{
			32,
			"sysboot",
			"System Boot"
		},
		{
			33,
			"64bme",
			"64-bit Memory Error"
		},
		{
			34,
			"mdev",
			"Management Device"
		},
		{
			35,
			"mdevc",
			"Management Device Component"
		},
		{
			36,
			"mdevtd",
			"Management Device Threshold Data"
		},
		{
			37,
			"mchannel",
			"Memory Channel"
		},
		{
			38,
			"ipmi",
			"IPMI Device"
		},
		{
			39,
			"powersupply",
			"Power Supply"
		},
		{
			40,
			"additional",
			"Additional Information"
		},
		{
			41,
			"onboarddev",
			"Onboard Device"
		},
		{
			42,
			"mchi",
			"Management Controller Host Interface"
		},
		{
			43,
			"TPM",
			"TPM Device"
		}

	};

	const Value::Type * Value::Type::find(uint8_t id) {

		for(size_t ix = 0; ix < (sizeof(types)/sizeof(types[0])); ix++) {

			if(types[ix].id == id) {
				return &types[ix];
			}

		}

		static const Value::Type deftype = {
			0xFF,
			"unknown",
			"unknown"
		};

		return &deftype;
	}


 }
