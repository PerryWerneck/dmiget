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

 using namespace std;

 namespace DMI {

	std::shared_ptr<DMI::Value> string_factory(const Header &header, const Value::Type *type, const Value::Record *record, uint8_t index) {

		class StringValue : public DMI::Value {
		private:
			string value;

		public:
			StringValue(const Value::Type *t, const Value::Record *r, const uint8_t i, const DMI::String &v) : DMI::Value(t,r,i), value(v.as_string()) {
			}

			virtual ~StringValue() {
			}

			std::string as_string() const override {
				return this->value;
			}

		};

		return make_shared<StringValue>(type,record,index,String(header,record->offset));

	}


	static const Value::Type types[] = {

		{
			0,
			false,
			"bios",
			"BIOS Information",
			(const Value::Record []) {
				{ "vendor",			string_factory,	1,	"Vendor"		},
				{ "version",		string_factory,	2,	"Version"		},
				{ "date",			string_factory,	3,	"Release Date"	},
				{}
			}
		},
		{
			1,
			false,
			"system",
			"System",
			(const Value::Record []) {
				{ "manufacturer",	string_factory,	1,	"Manufacturer"	},
				{ "name",			string_factory,	2,	"Product Name"	},
				{ "version",		string_factory,	3,	"Version"		},
				{ "serial",			string_factory,	4,	"Serial Number"	},
				{ "sku",			string_factory,	5,	"SKU Number"	},
				{ "family",			string_factory,	6,	"Family"		},
				{}
			}
		},
		{
			2,
			false,
			"baseboard",
			"Base Board",
			(const Value::Record []) {
				{ "manufacturer",	string_factory,	1,	"Manufacturer"			},
				{ "name",			string_factory,	2,	"Product Name"			},
				{ "version",		string_factory,	3,	"Version"				},
				{ "serial",			string_factory,	4,	"Serial Number"			},
				{ "atag",			string_factory,	5,	"Asset Tag"				},
				{ "location",		string_factory,	6,	"Location In Chassis"	},
				{}
			}
		},
		{
			3,
			false,
			"chassis",
			"Chassis Information",

			(const Value::Record []) {
				{ "manufacturer",	string_factory,	1,	"Manufacturer"	},
				{ "version",		string_factory,	2,	"Version"		},
				{ "serial",			string_factory,	3,	"Serial Number"	},
				{ "atag",			string_factory,	4,	"Asset Tag"		},
				{ "sku",			string_factory,	5,	"SKU Number"	},
				{}
			}

		},
		{
			4,
			false,
			"processor",
			"Processor",

			(const Value::Record []) {
				{ "socket",			string_factory,	1,	"Socket Designation"	},
				{ "manufacturer",	string_factory,	2,	"Manufacturer"	},
			//	{ "",	string_factory,	3,	""	},
			//	{ "",	string_factory,	4,	""	},
			//	{ "",	string_factory,	5,	""	},
			//	{ "",	string_factory,	6,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "socket",	string_factory,	1,	"Socket Designation"	},
				{}
			}
		},
		{
			8,
			true,
			"ports",
			"Port Connector",

			(const Value::Record []) {
				{ "internal",	string_factory,	1,	"Internal Reference Designator"	},
				{ "external",	string_factory,	2,	"External Reference Designator"	},
				{}
			}
		},
		{
			9,
			true,
			"slots",
			"System Slots",
			(const Value::Record []) {
				{ "designation",	string_factory,	1,	"Designation"	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "name",	string_factory,	1,	"Name"	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "locator",		string_factory,	1,	"Locator"		},
				{ "bank",			string_factory,	2,	"Bank Locator"	},
				{ "manufacturer",	string_factory,	3,	"Manufacturer"	},
				{ "serial",			string_factory,	4,	"Serial Number"	},
				{ "atag",			string_factory,	5,	"Asset Tag"		},
				{ "partnumber",		string_factory,	6,	"Part Number"	},
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
				{ "",	false,	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "location",		string_factory,	1,	"Location"			},
				{ "manufacturer",	string_factory,	2,	"Manufacturer"		},
				{ "date",			string_factory,	3,	"Manufacture Date"	},
				{ "serial",			string_factory,	4,	"Serial Number"		},
				{ "name",			string_factory,	5,	"Name"				},
				// { "",			string_factory,	6,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "description",	string_factory,	1,	"Description"	},
				{}
			}
		},
		{
			27,
			false,
			"cooling",
			"Cooling Device",
			(const Value::Record []) {
				{ "description",	string_factory,	1,	"Description"	},
				{}
			}
		},
		{
			28,
			false,
			"temperature",
			"Temperature Probe",
			(const Value::Record []) {
				{ "description",	string_factory,	1,	"Description"	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "location",		string_factory,	1,	"Location"			},
				{ "name",			string_factory,	2,	"Name"				},
				{ "manufacturer",	string_factory,	3,	"Manufacturer"		},
				{ "serial",			string_factory,	4,	"Serial Number"		},
				{ "atag",			string_factory,	5,	"Asset Tag"			},
				{ "modelpn",		string_factory,	6,	"Model Part Number"	},
				{ "revision",		string_factory,	7,	"Revision"			},
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
				{ "",	string_factory,	1,	""	},
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
				{ "reference",	string_factory,	1,	"Reference Designation"	},
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
				{ "",	string_factory,	1,	""	},
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
				{ "",	string_factory,	1,	""	},
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

		if(id >= 128) {

			static const Value::Type oemtype = {
				0xFF,
				true,
				"oem",
				"OEM-specific"
			};

			return &oemtype;
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
