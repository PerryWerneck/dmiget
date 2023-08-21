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
  * @brief SMBios types and decoders..
  */

/*
 * Based on dmidecode
 *
 * Copyright (C) 2000-2002 Alan Cox <alan@redhat.com>
 * Copyright (C) 2002-2020 Jean Delvare <jdelvare@suse.de>
 *
 */

 // References:
 //
 //		 https://github.com/acidanthera/dmidecode
 //

 #include <smbios/defs.h>
 #include <private/decoders.h>
 #include <private/decoders/memory.h>
 #include <private/decoders/processor.h>
 #include <private/decoders/bios.h>
 #include <private/decoders/system.h>
 #include <private/decoders/probe.h>

 #include <stdexcept>

 using namespace std;

 namespace SMBios {

	static const Decoder::Item EmptyTable[] = {
		{}
	};

	static const Decoder::Item BiosInformation[] = {
		{ "vendor",			Decoder::String{},				0x04,		"Vendor"				},
		{ "version",		Decoder::String{},				0x05,		"Version"				},
		{ "date",			Decoder::String{},				0x08,		"Release Date"			},
		{ "biosrev",		Decoder::FirmwareRevision{},	0x14,		"BIOS Revision"			},
		{ "firmwarerev",	Decoder::FirmwareRevision{},	0x16,		"Firmware Revision" 	},
		{}
	};

	static const Decoder::Item System[] = {
		{ "manufacturer",	Decoder::String{},				0x04,		"Manufacturer"			},
		{ "model",			Decoder::String{},				0x05,		"Product Name"			},
		{ "version",		Decoder::String{},				0x06,		"Version"				},
		{ "serial",			Decoder::String{},				0x07,		"Serial Number"			},
//		{ "uuid",			Decoder::SystemUUID{},			0x08,		"uuid"					},
//		{ "wakeup",			Decoder::SystemWakeUpType{},	0x18,		"Wake-up Type"			},
		{ "sku",			Decoder::String{},				0x19,		"SKU Number"			},
		{ "family",			Decoder::String{},				0x1A,		"Family"				},
		{}
	};

	static const Decoder::Item BaseBoard[] = {
		{ "manufacturer",	Decoder::String{},				0x04,		"Manufacturer"			},
		{ "model",			Decoder::String{},				0x05,		"Product Name"			},
		{ "version",		Decoder::String{},				0x06,		"Version"				},
		{ "serial",			Decoder::String{},				0x07,		"Serial Number"			},
		{ "atag",			Decoder::String{},				0x08,		"Asset Tag"				},
//		{ "features",		Decoder::BaseBoardFeatures{},	0x09,		"Base board features"	},
		{ "location",		Decoder::String{},				0x0A,		"Location In Chassis"	},
		{}
	};

	static const Decoder::Item Chassis[] = {
		{ "manufacturer",	Decoder::String{},				0x04,	"Manufacturer"				},
		// { "type",	Decoder::ChassisType{},				0x05,	"Type"				},
		// { "lock",	Decoder::ChassisLock{},				0x05,	"Lock"				},
		{ "version",		Decoder::String{},				0x06,	"Version"					},
		{ "serial",			Decoder::String{},				0x07,	"Serial Number"				},
		{ "atag",			Decoder::String{},				0x08,	"Asset Tag"					},
//		{ "sku",			Decoder::ChassisSKU{},			0x00,	"SKU Number"				},
		{}
	};


	static const Decoder::Item Processor[] = {
		{ "type",			Decoder::ProcessorType{},			0x05,	"Type"						},
		{ "socket",			Decoder::String{},					0x04,	"Socket Designation"		},
		{ "manufacturer",	Decoder::String{},					0x07,	"Manufacturer"				},
		{ "version",		Decoder::String{},					0x10,	"Version"					},
		{ "serial",			Decoder::String{},					0x20,	"Serial Number"				},
		{ "atag",			Decoder::String{},					0x21,	"Asset Tag"					},
		{ "partnumber",		Decoder::String{},					0x22,	"Part Number"				},
		{}
	};

	static const Decoder::Item Cache[] = {
		{ "socket",			Decoder::String{},					0x04,	"Socket Designation"	},
		{}
	};

	static const Decoder::Item PortConnectors[] = {
		{ "internal",		Decoder::String{},					0x04,	"Internal Reference Designator"	},
		{ "type",			Decoder::String{},					0x05,	"Internal Connector Type"		},
		{ "external",		Decoder::String{},					0x06,	"External Reference Designator"	},
		{}
	};

	static const Decoder::Item Slots[] = {
		{ "designation",	Decoder::String{},					0x04,	"Designation"					},
		{}
	};

	static const Decoder::Item GroupAssociations[] = {
		{ "name",			Decoder::String{},					0x04,	"Name"	},
		{}
	};

	static const Decoder::Item MemoryDevice[] = {
		{ "twidth",			Decoder::MemoryDeviceWidth{},		0x08,	"Total Width"		},
		{ "dwidth",			Decoder::MemoryDeviceWidth{},		0x0A,	"Data Width"		},
		{ "size",			Decoder::MemorySize{},				0x0C,	"Size"				},
		{ "formfactor",		Decoder::MemoryDeviceFormFactor{},	0x0E,	"Form Factor"		},
		{ "locator",		Decoder::String{},					0x10,	"Locator"			},
		{ "bank",			Decoder::String{},					0x11,	"Bank Locator"		},
		{ "manufacturer",	Decoder::String{},					0x17,	"Manufacturer"		},
		{ "serial",			Decoder::String{},					0x18,	"Serial Number"		},
		{ "atag",			Decoder::String{},					0x19,	"Asset Tag"			},
		{ "partnumber",		Decoder::String{},					0x1A,	"Part Number"		},

		{}
	};

	static const Decoder::Item PortableBattery[] = {
		{ "location",		Decoder::String{},					0x04,	"Location"			},
		{ "manufacturer",	Decoder::String{},					0x05,	"Manufacturer"		},
		{ "date",			Decoder::String{},					0x06,	"Manufacture Date"	},
		{ "serial",			Decoder::String{},					0x07,	"Serial Number"		},
		{ "name",			Decoder::String{},					0x08,	"Name"				},
		{}
	};

	static const Decoder::Item TemperatureProbe[] = {
		{ "description",	Decoder::String{},						0x04,	"Description"	},
//		{ "location",		Decoder::TemperatureProbeLocation{},	0x05,	"Location"	},
//		{ "status",			Decoder::TemperatureProbeStatus{},		0x05,	"Status"	},
		{ "maximum",		Decoder::TemperatureProbeValue{},		0x06,	"Maximum Value"	},
		{ "minimum",		Decoder::TemperatureProbeValue{},		0x08,	"Minimum Value"	},
		{ "tolerance",		Decoder::TemperatureProbeValue{},		0x08,	"Tolerance"	},
//		{ "accuracy",		Decoder::TemperatureProbeAccuracy{},	0x0E,	"Accuracy"	},
		{ "value",			Decoder::TemperatureProbeValue{},		0x14,	"Nominal Value"	},
		{}
	};

	static const Decoder::Item OnboardDevice[] = {
//		{ "reference",	Decoder::StringIndex{},	1,	"Reference Designation"	},
		{}
	};

	static const Decoder::Item PowerSupply[] = {
//		{ "location",		Decoder::StringIndex{},	1,	"Location"			},
//		{ "name",			Decoder::StringIndex{},	2,	"Name"				},
//		{ "manufacturer",	Decoder::StringIndex{},	3,	"Manufacturer"		},
//		{ "serial",			Decoder::StringIndex{},	4,	"Serial Number"		},
//		{ "atag",			Decoder::StringIndex{},	5,	"Asset Tag"			},
//		{ "modelpn",		Decoder::StringIndex{},	6,	"Model Part Number"	},
//		{ "revision",		Decoder::StringIndex{},	7,	"Revision"			},
		{}
	};

	static const Decoder::Item VoltageProbe[] = {
//		{ "description",	Decoder::StringIndex{},	1,	"Description"	},
		{}
	};

	static const Decoder::Item CoolingDevice[] = {
//		{ "description",	Decoder::StringIndex{},	1,	"Description"	},
		{}
	};

	static const Decoder::Type decoders[] = {

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
			"System Information",
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
			true,
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
			"OnBoardDevice",
			"On Board Devices Information",
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

	const Decoder::Type * Decoder::get(const uint8_t type) {

		if(type >= 128) {
			static const Decoder::Type oemtype {
				128,
				true,
				"oem",
				"OEM specific type",
				EmptyTable
			};
			return &oemtype;
		}

		for(const Decoder::Type &decoder : decoders) {
			if(decoder.type == type) {
				return &decoder;
			}
		}

#ifdef _MSC_VER
		char str[20];
		snprintf(str,19,"%u",(unsigned int) type);
		throw std::system_error(ENOENT,std::system_category(),string{"Invalid SMBIos structure type: "}+str);
#else
		throw std::system_error(ENOENT,std::system_category(),string{"Invalid SMBIos structure type: "}+std::to_string((int) type));
#endif // _MSC_VER

	}

	const Decoder::Type * Decoder::get(const char *name) {

		for(const Decoder::Type &decoder : decoders) {
			if(!strcasecmp(decoder.name,name)) {
				return &decoder;
			}
		}

		for(const Decoder::Type &decoder : decoders) {
			if(!strcasecmp(decoder.description,name)) {
				return &decoder;
			}
		}

		throw std::system_error(ENOENT,std::system_category(),string{"DMI:///"}+name+"/");

	}

	const Decoder::Type * Decoder::get(std::shared_ptr<Data> data, const int offset) {
		if(offset < 0) {
			return nullptr;
		}
		return get(*data->get(offset));
	}

 }

