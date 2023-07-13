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
 #include <functional>
 #include <cstring>

 using namespace std;
 namespace DMI = DMIget;

 static string input_file;
 static string delimiter{"\t"};

 static DMI::Table * TableFactory() {
	if(input_file.empty())
		return new DMI::Table();
	return new DMI::Table(input_file.c_str());
 }

 int main(int argc, char **argv) {

	static const struct Worker {
		char short_arg;
		const char *long_arg;
		const bool required;
		const char *help;
		const std::function<void(const char *argument)> method;

		Worker(char s, const char *l, const char *h, const bool r, const std::function<void(const char *argument)> m)
			: short_arg{s}, long_arg{l}, required{r}, help{h}, method{m} {
		}
	} workers[] {

		{
			'a',"all","",false,[](const char *) {

				auto table = TableFactory();

				table->for_each([](shared_ptr<DMI::Value> value){
					cout << value->url() << delimiter << value << endl;
					return true;
				});

				delete table;

			}
		},
		{
			'i',"urls","",false,[](const char *) {

				auto table = TableFactory();

				table->for_each([](shared_ptr<DMI::Value> value){
					cout << value->url() << endl;
					return true;
				});

				delete table;

			}
		},
		{
			'V',"values","",true,[](const char *filename) {

				auto table = TableFactory();

				table->for_each([](shared_ptr<DMI::Value> value){
					cout << value << endl;
					return true;
				});

				delete table;

			}
		},
		{
			'N',"names","",true,[](const char *filename) {

				auto table = TableFactory();

				table->for_each([](shared_ptr<DMI::Value> value){
					cout << value->name() << endl;
					return true;
				});

				delete table;

			}
		},
		{
			'I',"input-file","",true,[](const char *filename) {
				input_file = filename;
			}
		},
		{
			'D',"delimiter","",true,[](const char *d) {
				delimiter = d;
			}
		},
	};

	while(--argc) {

		bool found = false;
		const char *argument = *(++argv);

		if(!strncmp(argument,"--",2)) {

			argument += 2;
			const char *value = strchr(argument,'=');
			string name;
			if(value) {
				name.assign(argument,value-argument);
				value++;
			} else {
				name.assign(argument);
				value = "";
			}

			for(const Worker &worker : workers) {

				found = (strcmp(name.c_str(),worker.long_arg) == 0);
				if(found) {
					worker.method(value);
					break;
				}

			}

		}

		if(!found) {
			cerr << "Invalid argument" << endl;
			return -1;
		}

	}

	/*

	/// @brief Command line arguments.
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
			case 'i':	// Load table from filename.
				filename = optarg;
				break;

			case 'U':	// List URLs
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

			case 'V':	// List values
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

			case 'd':	// Setup delimiter for 'all' output
				delimiter = optarg;
				break;

			case 'a':	// List URLs and values.
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

	*/

	return 0;

 }
