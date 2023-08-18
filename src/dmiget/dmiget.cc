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

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <unistd.h>

 #include <smbios/node.h>
 #include <iostream>
 #include <iomanip>

 /*
 #include <functional>
 #include <cstring>
 #include <exception>

 #include <private/data.h>
 #include <smbios/memsize.h>
 */

 using namespace std;
 using namespace SMBios;

 int main(int argc, char **argv) {

	Node node{"system"};
	if(!node) {
		cout << "Cant find node" << endl;
		exit(-1);
	}

	cout << node.description() << endl << endl;

	auto value = node.begin();
	cout << value->description() << ": " << value->as_string() << endl;

	/*
	for(auto value : node) {
		cout << value->description() << ": " << value->as_string() << endl;
	}
	*/

	/*
 	for(Node node;node;node.next()) {
		cout << node.name() << endl;
		auto it = node.begin();
		cout << "---> " << it->name() << endl << endl;
 	}
 	*/

	return 0;
 }

 /*
 static bool verbose = true;
 static bool show_node = true;
 static bool show_value_label = true;
 static const char *filename = "";
 static const char *node_name = "";
 static const char *value_name = "";

 static enum OutputFormat : uint8_t {
	None,
	Complete,
	Urls
 } output_format = Complete;

 namespace Writer {

	class Abstract {
	public:
		virtual void write(const Node &node) = 0;
		virtual void write(const SMBios::Abstract::Value &value, bool tab = true) = 0;
		virtual void write(const char *url, const char *value) = 0;

		virtual void open() {
		}

		virtual void close() {
		}
	};

	class Text : public Abstract {
	public:
		void write(const Node &node) override {
			if(verbose) {
				cout	<< "Handle 0x" << setfill('0') << setw(4) << hex << node.handle() << dec
						<< ", DMI Type " << node.type() << ", " << node.size() << " bytes" << endl;
			}
			cout << node.description() << endl;
		}

		void write(const SMBios::Abstract::Value &value, bool tab) override {
			if(tab) {
				cout << "\t";
			}
			if(show_value_label) {
				cout << value.description() << ": ";
			}
			cout << value.as_string() << endl;
		}

		void write(const char *url, const char *value) override {
			cout << url << "\t" << value << endl;
		}

		void close() {
			cout << endl;
		}

	};

 }

 static std::shared_ptr<Writer::Abstract> writer{make_shared<Writer::Text>()};

 /// @brief Command-line arguments.
 static const struct Worker {
	char short_arg;
	const char *long_arg;
	const bool required;
	const char *help;
	const std::function<bool(const char *argument)> method;

	Worker(char s, const char *l, const char *h, const bool r, const std::function<bool(const char *argument)> m)
		: short_arg{s}, long_arg{l}, required{r}, help{h}, method{m} {
	}
 } workers[] {
	{
		'N',"node",
		"\t\tShow only nodes of required type",
		true,
		[](const char *name) {
			node_name = name;
			return false;
		}
	},
	{
		'V',"value",
		"\t\tShow only selected value",
		true,
		[](const char *name) {
			value_name = name;
			return false;
		}
	},
	{
		'v',"verbose",
		"\tVerbose output (default)",
		false,
		[](const char *) {
			verbose = true;
			return false;
		}
	},
	{
		'q',"quiet",
		"\t\tLess verbose output",
		false,
		[](const char *) {
			verbose = false;
			return false;
		}
	},
	{
		'u',"urls",
		"\t\tShow URLs and values",
		false,
		[](const char *) {
			output_format = Urls;
			return false;
		}
	},
	{
		'f',"dump-file",
		"\tRead from dump file",
		true,
		[](const char *arg) {
			filename = arg;
			return false;
		}
	},
	{
		'\0',"hide-nodes",
		"\tHide node information",
		false,
		[](const char *) {
			show_node = false;
			return false;
		}
	},
	{
		'\0',"hide-value-labels",
		"Hide value labels",
		false,
		[](const char *) {
			show_value_label = false;
			return false;
		}
	},
	{
		'D',"dump-table",
		"Dump data table",
		false,
		[](const char *) {

			char line[80];
			line[0] = 0;

			auto smbios = SMBios::Data::factory(filename);

			for(size_t offset = 0; offset < smbios->size(); offset++) {

				size_t col = offset%16;
				if(col == 0) {
					cout << line << endl;
					memset(line,' ',80);
					memset(line,'0',8);
					line[79] = 0;
					line[60] = line[77] = '|';
				}

				char buffer[10];

				const uint8_t *ptr = smbios->get(offset);
				snprintf(buffer,9,"%02x",*ptr);
				memcpy(line+(10+(col*3)),buffer,2);

				snprintf(buffer,9,"%08lx",offset);
				memcpy(line,buffer,8);

				line[61+col] = (*ptr >= ' ' && *ptr < 128) ? *ptr : '.';

			}
			cout << line << endl;


			return true;
		}
	},
	{
		'T',"text",
		"\t\tText mode output (default)",
		false,
		[](const char *) {
			writer = make_shared<Writer::Text>();
			return false;
		}
	}
 };

 int main(int argc, char **argv) {

	const char *appname = argv[0];

	try {

		// Check command-line arguments.

		while(--argc) {

			bool found = false;
			const char *argument = *(++argv);

			if(!(strcasecmp(argument,"--help") && strcmp(argument,"-h") && strcmp(argument,"-?") && strcmp(argument,"help") && strcmp(argument,"?"))) {

				cout << "Use " << appname << " [options] [dmi:///node/value]" << endl << endl;
				for(const Worker &worker : workers) {
					cout << "--" << worker.long_arg << "\t" << worker.help << endl;
				}
				return 0;

			} else if(!strncmp(argument,"--",2)) {

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
						if(worker.method(value)) {
							return 0;
						}
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

						if(worker.method(value)) {
							return 0;
						}
						break;

					}

				}

			} else if(strncasecmp(argument,"dmi:",4) == 0) {
				cout << Value::find(argument) << endl;
				output_format = None;
			}

		}

		switch(output_format) {
		case None:
			break;

		case Complete:
			// Show standard output.

			for(SMBios::Node node = Node::factory(filename,node_name);node;node.next(node_name)) {

				if(show_node) {

					writer->write(node);
					writer->open();

					node.for_each([](std::shared_ptr<Abstract::Value> value){
						if(!*value_name || strcasecmp(value_name,value->name()) == 0) {
							writer->write(*value);
						}
						return false;
					});

					writer->close();

				} else {

					node.for_each([](std::shared_ptr<Abstract::Value> value){
						if(!*value_name || strcasecmp(value_name,value->name()) == 0) {
							writer->write(*value,false);
						}
						return false;
					});

				}
			}
			break;

		case Urls:

			SMBios::Node::for_each([](const SMBios::Node &node, const size_t index, const Value &value) {
				string url{"dmi:///"};
				url += node.name();
				url += "/";
				if(index) {
					url += std::to_string(index);
					url += "/";
				}
				url += value.name();
				writer->write(url.c_str(),value.as_string().c_str());
				return false;
			});
			break;

		}

	} catch(const std::exception &e) {

		cerr << e.what() << endl;
		exit(-1);

	}

	return 0;
 }
 */

