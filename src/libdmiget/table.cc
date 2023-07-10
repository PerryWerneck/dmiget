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
 #include <dmiget/table.h>
 #include <cstring>
 #include <cerrno>
 #include <cstring>
 #include <iostream>
 #include <functional>

 using namespace std;

 #ifdef _MSC_VER
	#define strncasecmp  _strnicmp
	#define ftruncate    _chsize
	#define strtoull     _strtoui64
	#define strtoll      _strtoi64

	static __inline int strcasecmp (const char *s1, const char *s2) {
		size_t size1 = strlen(s1);
		size_t sisz2 = strlen(s2);
		return _strnicmp(s1, s2, sisz2 > size1 ? sisz2 : size1);
	}
 #endif // _MSC_VER

 namespace DMIget {

	static bool for_each(const uint8_t *buf, uint16_t num, uint32_t len, std::function<bool(const Header &header)> exec) {

		int i = 0;
		const uint8_t * data = buf;

		while ((i < num || !num) && data + 4 <= buf + len) {

			Header h{data};

			//
			// If a short entry is found (less than 4 bytes), not only it
			// is invalid, but we cannot reliably locate the next entry.
			// Also stop at end-of-table marker if so instructed.
			//
			if(h.length < 4 || h.type == 127) {
#ifdef DEBUG
				cout << "Aborting length=" << ((int) h.length) << " (min=4) type=" << ((int) h.type) << " (127=END)"<< endl;
#endif // DEBUG
				break;
			}

			i++;

			// Look for the next handle
			const uint8_t *next = data + h.length;

			while ((unsigned long)(next - buf + 1) < len && (next[0] != 0 || next[1] != 0))
				next++;
			next += 2;

			// Make sure the whole structure fits in the table
			if ((unsigned long)(next - buf) > len)
				break;

			// Call
			if(!exec(h)) {
				return false;
			}

			// Get next
			data = next;

		}

		return true;

	}

	bool Table::set(const uint8_t *d, size_t length) {

		if(dmi.contents) {
			delete[] dmi.contents;
		}

		dmi.contents = new uint8_t[length];
		dmi.len = (uint32_t) length;
		memcpy(dmi.contents,d,length);

		// Assign vendor for vendor-specific decodes later
		::DMIget::for_each(dmi.contents, dmi.num, dmi.len, [this](const Header &header) {

			if(header.type == 1 && header.length >= 6) {

				String vendor(header,header.data[0x04],0);
				String product(header,header.data[0x05],0);

				return false;
			}

			return true;
		});

		return true;
	}

	bool Table::for_each(std::function<bool(std::shared_ptr<Value> value)> exec) const {

		uint8_t typeindex[0x0100];
		memset(typeindex,0,sizeof(typeindex));

		return ::DMIget::for_each(dmi.contents, dmi.num, dmi.len,[this,exec,&typeindex](const Header &header) {

			const Value::Type * type = Value::Type::find(header.type);
			typeindex[type->id]++;

			if(type->records) {

				for(const Value::Record *record = type->records;record->name;record++) {

					auto value = record->value_factory(header,type,record,typeindex[type->id]);
					if(value) {
						if(!exec(value)) {
							return false;
						}
					}

				}

			} else if(type->name) {

				const char *bp = (const char *) header.data;
				size_t index = 0;

				bp += header.length;
				while(*bp) {

					Value::Record record;
					record.offset = ++index;
					record.description = "OEM String";

					if(!exec(make_shared<StringValue>(type,&record,typeindex[type->id],String(bp)))) {
						return false;
					}

					bp += strlen(bp);
					bp++;
				}

			}

			return true;
		});

	}

	std::shared_ptr<Value> Table::find(const char *url) const {

		std::shared_ptr<Value> found;

		if(!strncasecmp(url,"dmi:",4)) {
			url += 4;
		}

		while(*url && *url == '/') {
			url++;
		}

		for_each([&found,url](shared_ptr<Value> value){
			if(!strcasecmp(value->url().c_str()+6,url)) {
				found = value;
				return false;
			}

			return true;
		});

		return found;
	}

	std::string Table::operator[](const char *url) const {

		auto value = find(url);

		if(value) {
			return value->as_string();
		}

		return "";
	}


 }

