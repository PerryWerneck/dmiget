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

 #include <internals.h>

 namespace DMI {

	static const Value::Type types[] = {

		{
			0,
			false,
			"bios",
			"BIOS Information",
			(const Value::Record []) {
				{ "vendor",		Value::String,	1,	"Vendor"		},
				{ "version",	Value::String,	2,	"Version"		},
				{ "date",		Value::String,	3,	"Release Date"	},
				{}
			}
		},
		{
			1,
			false,
			"system",
			"System",
			(const Value::Record []) {
				{ "manufacturer",	Value::String,	1,	"Manufacturer"	},
				{ "name",			Value::String,	2,	"Product Name"	},
				{ "version",		Value::String,	3,	"Version"		},
				{ "serial",			Value::String,	4,	"Serial Number"	},
				{ "sku",			Value::String,	5,	"SKU Number"	},
				{ "family",			Value::String,	6,	"Family"		},
				{}
			}
		},
		{
			2,
			false,
			"baseboard",
			"Base Board",
			(const Value::Record []) {
				{ "manufacturer",	Value::String,	1,	"Manufacturer"			},
				{ "name",			Value::String,	2,	"Product Name"			},
				{ "version",		Value::String,	3,	"Version"				},
				{ "serial",			Value::String,	4,	"Serial Number"			},
				{ "atag",			Value::String,	5,	"Asset Tag"				},
				{ "location",		Value::String,	6,	"Location In Chassis"	},
				{}
			}
		},
		{
			3,
			false,
			"chassis",
			"Chassis Information",

			(const Value::Record []) {
				{ "manufacturer",	Value::String,	1,	"Manufacturer"	},
				{ "version",		Value::String,	2,	"Version"		},
				{ "serial",			Value::String,	3,	"Serial Number"	},
				{ "atag",			Value::String,	4,	"Asset Tag"		},
				{ "sku",			Value::String,	5,	"SKU Number"	},
				{}
			}

		},
		{
			4,
			false,
			"processor",
			"Processor",

			(const Value::Record []) {
				{ "socket",			Value::String,	1,	"Socket Designation"	},
				{ "manufacturer",	Value::String,	2,	"Manufacturer"	},
			//	{ "",	Value::String,	3,	""	},
			//	{ "",	Value::String,	4,	""	},
			//	{ "",	Value::String,	5,	""	},
			//	{ "",	Value::String,	6,	""	},
				{}
			}

		},
		{
			5,
			false,
			"mcntrl",
			"Memory Controller",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			6,
			false,
			"mmodule",
			"Memory Module",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			7,
			true,
			"cache",
			"Cache",
			(const Value::Record []) {
				{ "socket",	Value::String,	1,	"Socket Designation"	},
				{}
			}
		},
		{
			8,
			true,
			"ports",
			"Port Connector",

			(const Value::Record []) {
				{ "internal",	Value::String,	1,	"Internal Reference Designator"	},
				{ "external",	Value::String,	2,	"External Reference Designator"	},
				{}
			}
		},
		{
			9,
			true,
			"slots",
			"System Slots",
			(const Value::Record []) {
				{ "designation",	Value::String,	1,	"Designation"	},
				{}
			}
		},
		{
			10,
			false,
			"boarddevices",
			"On Board Devices",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			11,
			false,
			"oemstrings",
			"OEM Strings",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			12,
			false,
			"sysconf",
			"System Configuration Options",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			13,
			false,
			"language",
			"BIOS Language",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			14,
			true,
			"group",
			"Group Associations",
			(const Value::Record []) {
				{ "name",	Value::String,	1,	"Name"	},
				{}
			}
		},
		{
			15,
			false,
			"syslog",
			"System Event Log",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			16,
			false,
			"pma",
			"Physical Memory Array",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			17,
			true,
			"memory",
			"Memory Device",
			(const Value::Record []) {
				{ "locator",		Value::String,	1,	"Locator"		},
				{ "bank",			Value::String,	2,	"Bank Locator"	},
				{ "manufacturer",	Value::String,	3,	"Manufacturer"	},
				{ "serial",			Value::String,	4,	"Serial Number"	},
				{ "atag",			Value::String,	5,	"Asset Tag"		},
				{ "partnumber",		Value::String,	6,	"Part Number"	},
				{}
			}
		},
		{
			18,
			false,
			"32bme",
			"32-bit Memory Error",
			/*
			(const Value::Record []) {
				{ "",	false,	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			19,
			true,
			"mama",
			"Memory Array Mapped Address",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			20,
			false,
			"mdma",
			"Memory Device Mapped Address",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			21,
			false,
			"pointingdevice",
			"Built-in Pointing Device",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			22,
			false,
			"battery",
			"Portable Battery",
			(const Value::Record []) {
				{ "location",		Value::String,	1,	"Location"			},
				{ "manufacturer",	Value::String,	2,	"Manufacturer"		},
				{ "date",			Value::String,	3,	"Manufacture Date"	},
				{ "serial",			Value::String,	4,	"Serial Number"		},
				{ "name",			Value::String,	5,	"Name"				},
				// { "",			Value::String,	6,	""	},
				{}
			}

		},
		{
			23,
			false,
			"sysreset",
			"System Reset",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			24,
			false,
			"hwsecurity",
			"Hardware Security",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			25,
			false,
			"syspowercntrl",
			"System Power Controls",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			26,
			false,
			"vprobe",
			"Voltage Probe",
			(const Value::Record []) {
				{ "description",	Value::String,	1,	"Description"	},
				{}
			}
		},
		{
			27,
			false,
			"cooling",
			"Cooling Device",
			(const Value::Record []) {
				{ "description",	Value::String,	1,	"Description"	},
				{}
			}
		},
		{
			28,
			false,
			"temperature",
			"Temperature Probe",
			(const Value::Record []) {
				{ "description",	Value::String,	1,	"Description"	},
				{}
			}
		},
		{
			29,
			false,
			"electricalcurrent",
			"Electrical Current Probe",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			30,
			false,
			"ora",
			"Out-of-band Remote Access",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			31,
			false,
			"bis",
			"Boot Integrity Services",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			32,
			false,
			"sysboot",
			"System Boot",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			33,
			false,
			"64bme",
			"64-bit Memory Error",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			34,
			false,
			"mdev",
			"Management Device",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			35,
			false,
			"mdevc",
			"Management Device Component",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			36,
			false,
			"mdevtd",
			"Management Device Threshold Data",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			37,
			false,
			"mchannel",
			"Memory Channel",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			38,
			false,
			"ipmi",
			"IPMI Device",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			39,
			false,
			"powersupply",
			"Power Supply",
			(const Value::Record []) {
				{ "location",		Value::String,	1,	"Location"			},
				{ "name",			Value::String,	2,	"Name"				},
				{ "manufacturer",	Value::String,	3,	"Manufacturer"		},
				{ "serial",			Value::String,	4,	"Serial Number"		},
				{ "atag",			Value::String,	5,	"Asset Tag"			},
				{ "modelpn",		Value::String,	6,	"Model Part Number"	},
				{ "revision",		Value::String,	7,	"Revision"			},
				{}
			}
		},
		{
			40,
			false,
			"additional",
			"Additional Information",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			41,
			false,
			"onboarddev",
			"Onboard Device",
			(const Value::Record []) {
				{ "reference",	Value::String,	1,	"Reference Designation"	},
				{}
			}
		},
		{
			42,
			false,
			"mchi",
			"Management Controller Host Interface",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
		},
		{
			43,
			false,
			"TPM",
			"TPM Device",
			/*
			(const Value::Record []) {
				{ "",	Value::String,	1,	""	},
				{}
			}
			*/
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
			true,
			"unknown",
			"unknown"
		};

		return &deftype;
	}


 }
