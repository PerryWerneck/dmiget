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

	static const Root indexes[] = {
		{
			"BIOS",
			"BIOS Information",
			(const Child []) {
				{
					"Vendor"
				},
				{
					"Version"
				},
				{
					"Release Date"
				},
				{
					nullptr
				}
			}
		},
		{
			nullptr,
			"System"
		},
		{
			nullptr,
			"Base Board"
		},
		{
			nullptr,
			"Chassis"
		},
		{
			nullptr,
			"Processor"
		},
		{
			nullptr,
			"Memory Controller"
		},
		{
			nullptr,
			"Memory Module"
		},
		{
			nullptr,
			"Cache"
		},
		{
			nullptr,
			"Port Connector"
		},
		{
			nullptr,
			"System Slots"
		},
		{
			nullptr,
			"On Board Devices"
		},
		{
			nullptr,
			"OEM Strings"
		},
		{
			"sysconf",
			"System Configuration Options"
		},
		{
			nullptr,
			"BIOS Language"
		},
		{
			nullptr,
			"Group Associations"
		},
		{
			"syslog",
			"System Event Log"
		},
		{
			nullptr,
			"Physical Memory Array"
		},
		{
			nullptr,
			"Memory Device"
		},
		{
			nullptr,
			"32-bit Memory Error"
		},
		{
			nullptr,
			"Memory Array Mapped Address"
		},
		{
			nullptr,
			"Memory Device Mapped Address"
		},
		{
			nullptr,
			"Built-in Pointing Device"
		},
		{
			nullptr,
			"Portable Battery"
		},
		{
			nullptr,
			"System Reset"
		},
		{
			nullptr,
			"Hardware Security"
		},
		{
			nullptr,
			"System Power Controls"
		},
		{
			nullptr,
			"Voltage Probe"
		},
		{
			nullptr,
			"Cooling Device"
		},
		{
			nullptr,
			"Temperature Probe"
		},
		{
			nullptr,
			"Electrical Current Probe"
		},
		{
			nullptr,
			"Out-of-band Remote Access"
		},
		{
			nullptr,
			"Boot Integrity Services"
		},
		{
			"sysboot",
			"System Boot"
		},
		{
			nullptr,
			"64-bit Memory Error"
		},
		{
			nullptr,
			"Management Device"
		},
		{
			nullptr,
			"Management Device Component"
		},
		{
			nullptr,
			"Management Device Threshold Data"
		},
		{
			nullptr,
			"Memory Channel"
		},
		{
			"ipmi",
			"IPMI Device"
		},
		{
			nullptr,
			"Power Supply"
		},
		{
			nullptr,
			"Additional Information"
		},
		{
			nullptr,
			"Onboard Device"
		},
		{
			nullptr,
			"Management Controller Host Interface"
		},
		{
			"TPM",
			"TPM Device"
		},

		{
			nullptr
		}

	};



 }

