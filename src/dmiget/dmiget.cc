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

		} else if(argument[0] == '-') {

			argument++;

			if(argument[1]) {
				cerr << "Unexpected argument" << endl;
				return -1;
			}

			for(const Worker &worker : workers) {

				found = (worker.short_arg == argument[0]);
				if(found) {

					const char *value = "";

					if(worker.required) {

						if(argc == 1) {
							cerr << "An argument is required" << endl;
							exit(-1);
						}

						value = *(++argv);
						--argc;

						if(value[0] == '-') {
							cerr << "An argument is required" << endl;
							exit(-1);
						}

					}

					worker.method(value);
					break;

				}

			}

		} else {

			// It's an URL
			found = true;

			auto table = TableFactory();
			cout << table->find(argument) << endl;
			delete table;

		}

		if(!found) {
			cerr << "Invalid argument" << endl;
			return -1;
		}

	}

	return 0;

 }
