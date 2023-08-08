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

 #include <smbios/defs.h>
 #include <smbios/node.h>
 #include <smbios/value.h>
 #include <private/constants.h>

 namespace SMBios {

	static const Value::Info EmptyTable[] = {
		{}
	};

	static const Value::Info BiosInformation[] = {
		{ "vendor",			Decoder::String{},				1,		"Vendor"				},
		{ "version",		Decoder::String{},				2,		"Version"				},
		{ "date",			Decoder::String{},				3,		"Release Date"			},
		{ "biosrev",		Decoder::FirmwareRevision{},	0x14,	"BIOS Revision"			},
		{ "firmwarerev",	Decoder::FirmwareRevision{},	0x16,	"Firmware Revision" 	},
		{}
	};

	static const Value::Info System[] = {
		{ "manufacturer",	Decoder::String{},				1,		"Manufacturer"			},
		{ "name",			Decoder::String{},				2,		"Product Name"			},
		{ "version",		Decoder::String{},				3,		"Version"				},
		{ "serial",			Decoder::String{},				4,		"Serial Number"			},
		{ "sku",			Decoder::String{},				5,		"SKU Number"			},
		{ "family",			Decoder::String{},				6,		"Family"				},
		{}
	};

	static const Value::Info BaseBoard[] = {
		{ "manufacturer",	Decoder::String{},				1,		"Manufacturer"			},
		{ "name",			Decoder::String{},				2,		"Product Name"			},
		{ "version",		Decoder::String{},				3,		"Version"				},
		{ "serial",			Decoder::String{},				4,		"Serial Number"			},
		{ "atag",			Decoder::String{},				5,		"Asset Tag"				},
		{ "location",		Decoder::String{},				6,		"Location In Chassis"	},
		{}
	};

	static const Value::Info Chassis[] = {
		{ "manufacturer",	Decoder::String{},				1,	"Manufacturer"				},
		{ "version",		Decoder::String{},				2,	"Version"					},
		{ "serial",			Decoder::String{},				3,	"Serial Number"				},
		{ "atag",			Decoder::String{},				4,	"Asset Tag"					},
		{ "sku",			Decoder::String{},				5,	"SKU Number"				},
		{}
	};

	static const Value::Info Processor[] = {
		{ "socket",			Decoder::String{},				1,	"Socket Designation"		},
		{ "manufacturer",	Decoder::String{},				2,	"Manufacturer"				},
		{}
	};


	static const Value::Info Cache[] = {
		{ "socket",			Decoder::String{},	1,	"Socket Designation"	},
		{}
	};

	static const Value::Info PortConnectors[] = {
		{ "internal",	Decoder::String{},	1,	"Internal Reference Designator"	},
		{ "external",	Decoder::String{},	2,	"External Reference Designator"	},
		{}
	};

	static const Value::Info Slots[] = {
		{ "designation",	Decoder::String{},	1,	"Designation"	},
		{}
	};

	static const Value::Info GroupAssociations[] = {
		{ "name",	Decoder::String{},	1,	"Name"	},
		{}
	};

	static const Value::Info MemoryDevice[] = {
		{ "locator",		Decoder::String{},	1,	"Locator"		},
		{ "bank",			Decoder::String{},	2,	"Bank Locator"	},
		{ "manufacturer",	Decoder::String{},	3,	"Manufacturer"	},
		{ "serial",			Decoder::String{},	4,	"Serial Number"	},
		{ "atag",			Decoder::String{},	5,	"Asset Tag"		},
		{ "partnumber",		Decoder::String{},	6,	"Part Number"	},
		{}
	};

	static const Value::Info PortableBattery[] = {
		{ "location",		Decoder::String{},	1,	"Location"			},
		{ "manufacturer",	Decoder::String{},	2,	"Manufacturer"		},
		{ "date",			Decoder::String{},	3,	"Manufacture Date"	},
		{ "serial",			Decoder::String{},	4,	"Serial Number"		},
		{ "name",			Decoder::String{},	5,	"Name"				},
		{}
	};

	static const Value::Info TemperatureProbe[] = {
		{ "description",	Decoder::String{},	1,	"Description"	},
		{}
	};

	static const Value::Info OnboardDevice[] = {
		{ "reference",	Decoder::String{},	1,	"Reference Designation"	},
		{}
	};

	static const Value::Info PowerSupply[] = {
		{ "location",		Decoder::String{},	1,	"Location"			},
		{ "name",			Decoder::String{},	2,	"Name"				},
		{ "manufacturer",	Decoder::String{},	3,	"Manufacturer"		},
		{ "serial",			Decoder::String{},	4,	"Serial Number"		},
		{ "atag",			Decoder::String{},	5,	"Asset Tag"			},
		{ "modelpn",		Decoder::String{},	6,	"Model Part Number"	},
		{ "revision",		Decoder::String{},	7,	"Revision"			},
		{}
	};

	static const Value::Info VoltageProbe[] = {
		{ "description",	Decoder::String{},	1,	"Description"	},
		{}
	};

	static const Value::Info CoolingDevice[] = {
		{ "description",	Decoder::String{},	1,	"Description"	},
		{}
	};

	static const Node::Info types[] = {

		{
			0,
			false,
			"BIOS",
			"BIOS Information",
			BiosInformation
		},
		{
			1,
			false,
			"System",
			"System",
			System
		},
		{
			2,
			false,
			"BaseBoard",
			"Base Board",
			BaseBoard
		},
		{
			3,
			false,
			"Chassis",
			"Chassis Information",
			Chassis
		},
		{
			4,
			false,
			"Processor",
			"Processor",
			Processor
		},
		{
			5,
			false,
			"MemoryController",
			"Memory Controller",
			EmptyTable
		},
		{
			6,
			false,
			"MemoryModule",
			"Memory Module",
			EmptyTable
		},
		{
			7,
			true,
			"Cache",
			"Cache",
			Cache
		},
		{
			8,
			true,
			"PortConnectors",
			"Port Connector",
			PortConnectors
		},
		{
			9,
			true,
			"Slots",
			"System Slots",
			Slots
		},
		{
			10,
			false,
			"OnBoardDevices",
			"On Board Devices",
			EmptyTable
		},
		{
			11,
			false,
			"OEMstrings",
			"OEM Strings",
			EmptyTable
		},
		{
			12,
			false,
			"SysConfigOpts",
			"System Configuration Options",
			EmptyTable
		},
		{
			13,
			false,
			"BIOSLanguage",
			"BIOS Language",
			EmptyTable
		},
		{
			14,
			true,
			"GroupAssociations",
			"Group Associations",
			GroupAssociations
		},
		{
			15,
			false,
			"EventLog",
			"System Event Log",
			EmptyTable
		},
		{
			16,
			false,
			"PhysicalMemoryArray",
			"Physical Memory Array",
			EmptyTable
		},
		{
			17,
			true,
			"MemoryDevice",
			"Memory Device",
			MemoryDevice
		},
		{
			18,
			false,
			"32BitMemoryError",
			"32-bit Memory Error",
			EmptyTable
		},
		{
			19,
			true,
			"MemoryArrayAddressMap",
			"Memory Array Mapped Address",
			EmptyTable
		},
		{
			20,
			false,
			"MemoryDeviceAddressMap",
			"Memory Device Mapped Address",
			EmptyTable
		},
		{
			21,
			false,
			"BuiltinPointingDevice",
			"Built-in Pointing Device",
			EmptyTable
		},
		{
			22,
			false,
			"PortableBattery",
			"Portable Battery",
			PortableBattery
		},
		{
			23,
			false,
			"SystemReset",
			"System Reset",
			EmptyTable
		},
		{
			24,
			false,
			"HWsecurity",
			"Hardware Security",
			EmptyTable
		},
		{
			25,
			false,
			"SysPowerCtrl",
			"System Power Controls",
			EmptyTable
		},
		{
			26,
			false,
			"VoltageProbe",
			"Voltage Probe",
			VoltageProbe
		},
		{
			27,
			false,
			"CoolingDevice",
			"Cooling Device",
			CoolingDevice
		},
		{
			28,
			false,
			"TemperatureProbe",
			"Temperature Probe",
			TemperatureProbe
		},
		{
			29,
			false,
			"ElectricalCurrentProbe",
			"Electrical Current Probe",
			EmptyTable
		},
		{
			30,
			false,
			"RemoteAccess",
			"Out-of-band Remote Access",
			EmptyTable
		},
		{
			31,
			false,
			"BootIntegritySrv",
			"Boot Integrity Services",
			EmptyTable
		},
		{
			32,
			false,
			"SystemBoot",
			"System Boot",
			EmptyTable
		},
		{
			33,
			false,
			"64BitMemoryError",
			"64-bit Memory Error",
			EmptyTable
		},
		{
			34,
			false,
			"ManagementDevice",
			"Management Device",
			EmptyTable
		},
		{
			35,
			false,
			"ManagementDeviceComponent",
			"Management Device Component",
			EmptyTable
		},
		{
			36,
			false,
			"ManagementDeviceThreshold",
			"Management Device Threshold Data",
			EmptyTable
		},
		{
			37,
			false,
			"MemoryChannel",
			"Memory Channel",
			EmptyTable
		},
		{
			38,
			false,
			"IPMIdevice",
			"IPMI Device",
			EmptyTable
		},
		{
			39,
			false,
			"PowerSupply",
			"Power Supply",
			PowerSupply
		},
		{
			40,
			false,
			"AdditionalInfo",
			"Additional Information",
			EmptyTable
		},
		{
			41,
			false,
			"OnboardDevice",
			"Onboard Device",
			OnboardDevice
		},
		{
			42,
			false,
			"MgmntCtrltHostIntf",
			"Management Controller Host Interface",
			EmptyTable
		},
		{
			43,
			false,
			"TPMDevice",
			"TPM Device",
			EmptyTable
		}

	};

	const Node::Info * Node::Info::find(uint8_t id) {

		for(size_t ix = 0; ix < (sizeof(types)/sizeof(types[0])); ix++) {

			if(types[ix].id == id) {
				return types+ix;
			}

		}

		if(id >= 128) {

			static const Node::Info oemtype = {
				0xFF,
				true,
				"oem",
				"OEM-specific"
			};

			return &oemtype;
		}

		static const Node::Info deftype = {
			0xFF,
			true,
			"unknown",
			"unknown"
		};

		return &deftype;
	}

 }
