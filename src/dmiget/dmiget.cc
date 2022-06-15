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
 #include <dmiget/table.h>
 #include <iostream>
 #include <getopt.h>

 using namespace std;
 namespace DMI = DMIget;

 int main(int argc, char **argv) {

	static struct option options[] = {
		{ "all",			no_argument,		0,	'a' },
		{ "urls",			no_argument,		0,	'U' },
		{ "values",			no_argument,		0,	'V' },
		{ "input-file",		required_argument,	0,	'i' },
		{ "delimiter",		required_argument,	0,	'd' },
	};

	try {

		string delimiter{"\t"};
		const char *filename = nullptr;

		int long_index =0;
		int opt;
		while((opt = getopt_long(argc, argv, "UVad:i:", options, &long_index )) != -1) {

			switch(opt) {
			case 'd':
				delimiter = optarg;
				break;

			case 'i':
				filename = optarg;
				break;

			case 'U':
				{
					const DMI::Table * table = nullptr;

					if(filename) {
						table = new DMI::Table(filename);
					} else {
						table = new DMI::Table();
					}

					table->for_each([](shared_ptr<DMI::Value> value){
						cout << value->url() << endl;
						return true;
					});

					delete table;
				}
				break;

			case 'V':
				{
					const DMI::Table * table = nullptr;

					if(filename) {
						table = new DMI::Table(filename);
					} else {
						table = new DMI::Table();
					}

					table->for_each([](shared_ptr<DMI::Value> value){
						cout << value << endl;
						return true;
					});

					delete table;
				}
				break;

			case 'a':
				{
					const DMI::Table * table = nullptr;

					if(filename) {
						table = new DMI::Table(filename);
					} else {
						table = new DMI::Table();
					}

					table->for_each([delimiter](shared_ptr<DMI::Value> value){
						cout << value->url() << delimiter << value << endl;
						return true;
					});

					delete table;
				}
				break;

			}

		}

		if(optind < argc) {

			const DMI::Table * table = nullptr;

			if(filename) {
				table = new DMI::Table(filename);
			} else {
				table = new DMI::Table();
			}

			for(; optind < argc; optind++) {
				cout << table->find((const char *) argv[optind]) << endl;
			}

			delete table;
		}


	} catch(const exception &e) {

		cerr << endl << e.what() << endl;
		return -1;
	}

	return 0;

 }
