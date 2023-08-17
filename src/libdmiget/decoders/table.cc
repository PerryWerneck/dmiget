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

 #include <smbios/defs.h>
 #include <private/decoders.h>
 #include <stdexcept>

 using namespace std;

 namespace SMBios {

	static const Decoder::Item NoDecoders[] = {
		{}
	};

	static const Decoder::Generic decoders[] = {
		Decoder::Generic {
			0,false,"BIOS","BIOS Information",
			(const Decoder::Item[]) {
				Decoder::String{ "vendor", "Vendor", 0x04, },
				Decoder::String{ "version", "Version", 0x05, },
				Decoder::String{ "date", "Release Date", 0x08, },
				//Decoder::FirmwareRevision{ "biosrev", "BIOS Revision", 0x14 },
				//Decoder::FirmwareRevision{ "firmwarerev", "Firmware Revision", 0x16 },
				{}
			}

		},
		Decoder::Generic {
			1,false,"System","System Information",
			(const Decoder::Item []) {
				Decoder::String{ "manufacturer", "Manufacturer", 0x04},
				Decoder::String{ "model", "Product Name", 0x05},
				Decoder::String{ "version", "Version", 0x06},
				Decoder::String{ "serial", "Serial Number", 0x07},
		//		Decoder::SystemUUID{ "uuid", "uuid", 0x08},
		//		Decoder::SystemWakeUpType{ "wakeup", "Wake-up Type", 0x18},
				Decoder::String{ "sku", "SKU Number", 0x19},
				Decoder::String{ "family", "Family", 0x1A},
				{}
			}
		},
		Decoder::Generic {
			2,false,"BaseBoard","Base Board",
			(const Decoder::Item []) {
				Decoder::String{ "manufacturer", "Manufacturer", 0x04},
				Decoder::String{ "model", "Product Name", 0x05},
				Decoder::String{ "version", "Version", 0x06},
				Decoder::String{ "serial", "Serial Number", 0x07},
				Decoder::String{ "atag", "Asset Tag", 0x08},
		//		Decoder::BaseBoardFeatures{ "features", "Base board features", 0x09},
				Decoder::String{ "location", "Location In Chassis", 0x0A},
				{}
			}
		},
		Decoder::Generic {
			3,false,"Chassis","Chassis Information",
			(const Decoder::Item []) {
				Decoder::String{ "manufacturer", "Manufacturer", 0x04},
		//		Decoder::ChassisType{ "type", "Type", 0x05},
		//		Decoder::ChassisLock{ "lock", "Lock", 0x05},
				Decoder::String{ "version", "Version", 0x06},
				Decoder::String{ "serial", "Serial Number", 0x07},
				Decoder::String{ "atag", "Asset Tag", 0x08},
		//		Decoder::ChassisSKU{ "sku", "SKU Number", 0x00},
				{}
			}
		},
		Decoder::Generic {
			4,true,"Processor","Processor",
			(const Decoder::Item []) {
		//		Decoder::ProcessorType{ "type", "Type", 0x05},
				Decoder::String{ "socket", "Socket Designation", 0x04},
				Decoder::String{ "manufacturer", "Manufacturer", 0x07},
				Decoder::String{ "version", "Version", 0x10},
				Decoder::String{ "serial", "Serial Number", 0x20},
				Decoder::String{ "atag", "Asset Tag", 0x21},
				Decoder::String{ "partnumber", "Part Number", 0x22},
				{}
			}
		},
		Decoder::Generic {
			5,false,"MemoryController","Memory Controller",
			NoDecoders
		},
		Decoder::Generic {
			6,false,"MemoryModule","Memory Module",
			NoDecoders
		},
		Decoder::Generic {
			7,true,"Cache","Cache",
			(const Decoder::Item []) {
				Decoder::String{ "socket", "Socket Designation", 0x04},
				{}
			}
		},
		Decoder::Generic {
			8,true,"PortConnectors","Port Connector",
			(const Decoder::Item []) {
				Decoder::String{ "internal", "Internal Reference Designator", 0x04},
				Decoder::String{ "type", "Internal Connector Type", 0x05},
				Decoder::String{ "external", "External Reference Designator", 0x06},
				{}
			}
		},
		Decoder::Generic {
			9,true,"Slots","System Slots",
			(const Decoder::Item []) {
				Decoder::String{ "designation", "Designation", 0x04},
				{}
			}
		},
		Decoder::Generic {
			10,false,"OnBoardDevice","On Board Devices Information",
			NoDecoders
		},
		Decoder::Generic {
			11,false,"OEMstrings","OEM Strings",
			NoDecoders
		},
		Decoder::Generic {
			12,false,"SysConfigOpts","System Configuration Options",
			NoDecoders
		},
		Decoder::Generic {
			13,false,"BIOSLanguage","BIOS Language",
			NoDecoders
		},
		Decoder::Generic {
			14,true,"GroupAssociations","Group Associations",
			(const Decoder::Item []) {
				{ "name", "Name", 0x04},
				{}
			}
		},
		Decoder::Generic {
			15,false,"EventLog","System Event Log",
			NoDecoders
		},
		{
			16,false,"PhysicalMemoryArray","Physical Memory Array",
			NoDecoders
		},
		Decoder::Generic {
			17,true,"MemoryDevice","Memory Device",
			(const Decoder::Item []) {
		//		Decoder::MemoryDeviceWidth{ "twidth", "Total Width", 0x08},
		//		Decoder::MemoryDeviceWidth{ "dwidth", "Data Width", 0x0A},
		//		Decoder::MemorySize{ "size", "Size", 0x0C},
		//		Decoder::MemoryDeviceFormFactor{ "formfactor", "Form Factor", 0x0E},
				Decoder::String{ "locator", "Locator", 0x10},
				Decoder::String{ "bank", "Bank Locator", 0x11},
				Decoder::String{ "manufacturer", "Manufacturer", 0x17},
				Decoder::String{ "serial", "Serial Number", 0x18},
				Decoder::String{ "atag", "Asset Tag", 0x19},
				Decoder::String{ "partnumber", "Part Number", 0x1A},
				{}
			}
		},
		Decoder::Generic {
			18,false,"32BitMemoryError","32-bit Memory Error",
			NoDecoders
		},
		Decoder::Generic {
			19,true,"MemoryArrayAddressMap","Memory Array Mapped Address",
			NoDecoders
		},
		Decoder::Generic {
			20,false,"MemoryDeviceAddressMap","Memory Device Mapped Address",
			NoDecoders
		},
		Decoder::Generic {
			21,false,"BuiltinPointingDevice","Built-in Pointing Device",
			NoDecoders
		},
		Decoder::Generic {
			22,false,"PortableBattery","Portable Battery",
			(const Decoder::Item []) {
				Decoder::String{ "location", "Location", 0x04},
				Decoder::String{ "manufacturer", "Manufacturer", 0x05},
				Decoder::String{ "date", "Manufacture Date", 0x06},
				Decoder::String{ "serial", "Serial Number", 0x07},
				Decoder::String{ "name", "Name", 0x08},
				{}
			}
		},
		Decoder::Generic {
			23,false,"SystemReset","System Reset",
			NoDecoders
		},
		Decoder::Generic {
			24,false,"HWsecurity","Hardware Security",
			NoDecoders
		},
		Decoder::Generic {
			25,false,"SysPowerCtrl","System Power Controls",
			NoDecoders
		},
		Decoder::Generic {
			26,false,"VoltageProbe","Voltage Probe",
			(const Decoder::Item []) {
		//		{ "description", Decoder::StringIndex{}, 1, "Description"},
				{}
			}
		},
		Decoder::Generic {
			27,false,"CoolingDevice","Cooling Device",
			(const Decoder::Item []) {
		//		{ "description", Decoder::StringIndex{}, 1, "Description"},
				{}
			}
		},
		Decoder::Generic {
			28,false,"TemperatureProbe","Temperature Probe",
			(const Decoder::Item []) {
				Decoder::String{ "description", "Description", 0x04},
		//		Decoder::TemperatureProbeLocation{ "location", "Location", 0x05},
		//		Decoder::TemperatureProbeStatus{ "status", "Status", 0x05},
		//		Decoder::TemperatureProbeValue{ "maximum", "Maximum Value", 0x06},
		//		Decoder::TemperatureProbeValue{ "minimum", 0x08, "Minimum Value"},
		//		Decoder::TemperatureProbeValue{ "tolerance", "Tolerance", 0x08},
		//		Decoder::TemperatureProbeAccuracy{ "accuracy", "Accuracy", 0x0E},
		//		Decoder::TemperatureProbeValue{ "value", "Nominal Value", 0x14},
				{}
			}
		},
		Decoder::Generic {
			29,false,"ElectricalCurrentProbe","Electrical Current Probe",
			NoDecoders
		},
		Decoder::Generic {
			30,false,"RemoteAccess","Out-of-band Remote Access",
			NoDecoders
		},
		Decoder::Generic {
			31,false,"BootIntegrityServices","Boot Integrity Services",
			NoDecoders
		},
		Decoder::Generic {
			32,false,"SystemBoot","System Boot",
			NoDecoders
		},
		Decoder::Generic {
			33,false,"64BitMemoryError","64-bit Memory Error",
			NoDecoders
		},
		Decoder::Generic {
			34,false,"ManagementDevice","Management Device",
			NoDecoders
		},
		Decoder::Generic {
			35,false,"ManagementDeviceComponent","Management Device Component",
			NoDecoders
		},
		Decoder::Generic {
			36,false,"ManagementDeviceThreshold","Management Device Threshold Data",
			NoDecoders
		},
		Decoder::Generic {
			37,false,"MemoryChannel","Memory Channel",
			NoDecoders
		},
		Decoder::Generic {
			38,false,"IPMIdevice","IPMI Device",
			NoDecoders
		},
		Decoder::Generic {
			39,false,"PowerSupply","Power Supply",
			(const Decoder::Item []) {
		//		{ "location", Decoder::StringIndex{}, 1, "Location"},
		//		{ "name", Decoder::StringIndex{}, 2, "Name"},
		//		{ "manufacturer", Decoder::StringIndex{}, 3, "Manufacturer"},
		//		{ "serial", Decoder::StringIndex{}, 4, "Serial Number"},
		//		{ "atag", Decoder::StringIndex{}, 5, "Asset Tag"},
		//		{ "modelpn", Decoder::StringIndex{}, 6, "Model Part Number"},
		//		{ "revision", Decoder::StringIndex{}, 7, "Revision"},
				{}
			}
		},
		Decoder::Generic {
			40,false,"AdditionalInfo","Additional Information",
			NoDecoders
		},
		Decoder::Generic {
			41,true,"OnboardDevice","Onboard Device",
			(const Decoder::Item []) {
		//		{ "reference", Decoder::StringIndex{}, 1, "Reference Designation"},
				{}
			}
		},
		Decoder::Generic {
			42,false,"MgmntCtrltHostIntf","Management Controller Host Interface",
			NoDecoders
		},
		Decoder::Generic {
			43,false,"TPMDevice","TPM Device",
			NoDecoders
		}

	};

	const Decoder::Generic * Decoder::get(const uint8_t type) {

		if(type >= 128) {
			// Is a generic OEM type.
			static const Decoder::Generic OEMType {
				128,true,"oem","OEM-specific",
				NoDecoders
			};

			return &OEMType;

		}

		for(const Decoder::Generic &decoder : decoders) {
			if(decoder.type == type) {
				return &decoder;
			}
		}

		throw std::system_error(ENOENT,std::system_category(),string{"SMBIos::"}+to_string((int) type));

	}

	const Decoder::Generic * Decoder::get(const char *name) {

		for(const Decoder::Generic &decoder : decoders) {
			if(!strcasecmp(decoder.name,name)) {
				return &decoder;
			}
		}

		for(const Decoder::Generic &decoder : decoders) {
			if(!strcasecmp(decoder.description,name)) {
				return &decoder;
			}
		}

		throw std::system_error(ENOENT,std::system_category(),string{"SMBIos::"}+name);

	}

	const Decoder::Generic * Decoder::get(std::shared_ptr<Data> data, const int offset) {
		if(offset < 0) {
			return nullptr;
		}
		return get(*data->get(offset));
	}

 }
