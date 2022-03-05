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

 namespace DMIget {

	class VersionValue : public DMI::Value {
	private:
		int ma, mi;

	public:
		VersionValue(const Value::Type *t, const Value::Record *r, const uint8_t i, int p1, int p2) : DMI::Value(t,r,i), ma(p1), mi(p2) {
		}

		unsigned int as_uint() const override {
			return (ma << 8) | (mi & 0xFF);
		}

		std::string as_string() const override {
			string value = to_string(ma);
			value += '.';
			value += to_string(mi);
			return value;
		}

	};

	shared_ptr<DMI::Value> string_factory(const Header &header, const Value::Type *type, const Value::Record *record, uint8_t index) {
		return make_shared<StringValue>(type,record,index,String(header,record->offset));
	}

	shared_ptr<DMI::Value> firmware_revision_factory(const Header &header, const Value::Type *type, const Value::Record *record, uint8_t index) {

		if(header.length > (record->offset+1) && header.data[record->offset] != 0xFF && header.data[record->offset+1] != 0xFF) {
			return make_shared<VersionValue>(type,record,index,header.data[record->offset], header.data[record->offset+1]);
		}

		return shared_ptr<DMI::Value>();
	}




 }
