#include<string>
#include<iostream>
using namespace std;

class fix {
private:
	string info;
	string info_35;
	string info_39;
	string info_38;
	string info_44;
	string info_151;
	string info_14;
	string info_31;
	string info_32;
	string info_6;
	string orderid;
	string buyerid;
public:
	fix(string str) {
		info = str;
	};
	string fix::Get_35() {
		int pos;
		pos = info.find("35=", 0);
		info_35 = info.substr(pos + 3, 1);
		if (info_35 != "D"&&info_35 != "F"&&info_35 != "8"&&info_35 != "9") {
			return "Invalid FIX message.";
		}
		else {
			return info_35;
		}
	};
	int fix::Get_38() {
		int pos;
		int pos2;
		pos = info.find("38=", 0);
		for (int i = pos; info[i] != '\n'; ++i) {
			if (info[i] == ' '){
				pos2 = i;
			}
		}
		info_38 = info.substr(pos+3,pos2 - pos);
		int price = stoi(info_38);
		return price;
	}
	int fix::Get_44() {
		int pos;
		int pos2;
		pos = info.find("44=", 0);
		for (int i = pos; info[i] != '\n'; ++i) {
			if (info[i] == ' ') {
				pos2 = i;
			}
		}
		info_44 = info.substr(pos + 3, pos2 - pos);
		int quantity = stoi(info_44);
		return quantity;
	}
	string fix::Get_11() {
		int pos;
		int pos2;
		pos = info.find("11=", 0);
		for (int i = pos; info[i] != '\n'; ++i) {
			if (info[i] == ' ') {
				pos2 = i;
			}
		}
		orderid = info.substr(pos + 3, pos2 - pos);
		return orderid;
	}
	string fix::Get_41() {
		int pos;
		int pos2;
		pos = info.find("41=", 0);
		for (int i = pos; info[i] != '\n'; ++i) {
			if (info[i] == ' ') {
				pos2 = i;
			}
		}
		orderid = info.substr(pos + 3, pos2 - pos);
		return orderid;
	}
	string fix::Get_39() {
		int pos;
		pos = info.find("39=", 0);
		info_39 = info.substr(pos + 3, 1);
		if (info_39 != "0"&&info_39 != "1"&&info_39 != "2"&&info_39 != "8"&&info_39 != "9") {
			return "Invalid FIX message.";
		}
		else {
			return info_39;
		}
	}
	int fix::Get_151() {
		int pos;
		int pos2;
		pos = info.find("151=", 0);
		for (int i = pos; info[i] != '\n'; ++i) {
			if (info[i] == ' ') {
				pos2 = i;
			}
		}
		info_151 = info.substr(pos + 3, pos2 - pos);
		int left_quantity= stoi(info_151);
		return left_quantity;
	}
	int fix::Get_14() {
		int pos;
		int pos2;
		pos = info.find("14=", 0);
		for (int i = pos; info[i] != '\n'; ++i) {
			if (info[i] == ' ') {
				pos2 = i;
			}
		}
		info_14 = info.substr(pos + 3, pos2 - pos);
		int shared_quantity = stoi(info_14);
		return shared_quantity;
	}
	int fix::Get_31() {
		int pos;
		int pos2;
		pos = info.find("31=", 0);
		for (int i = pos; info[i] != '\n'; ++i) {
			if (info[i] == ' ') {
				pos2 = i;
			}
		}
		info_31 = info.substr(pos + 3, pos2 - pos);
		int last_price = stoi(info_31);
		return last_price;
	}
	int fix::Get_31() {
		int pos;
		int pos2;
		pos = info.find("31=", 0);
		for (int i = pos; info[i] != '\n'; ++i) {
			if (info[i] == ' ') {
				pos2 = i;
			}
		}
		info_31 = info.substr(pos + 3, pos2 - pos);
		int last_price = stoi(info_31);
		return last_price;
	}
	int fix::Get_32() {
		int pos;
		int pos2;
		pos = info.find("32=", 0);
		for (int i = pos; info[i] != '\n'; ++i) {
			if (info[i] == ' ') {
				pos2 = i;
			}
		}
		info_32 = info.substr(pos + 3, pos2 - pos);
		int last_quantity = stoi(info_32);
		return last_quantity;
	}
	int fix::Get_6() {
		int pos;
		int pos2;
		pos = info.find("6=", 0);
		for (int i = pos; info[i] != '\n'; ++i) {
			if (info[i] == ' ') {
				pos2 = i;
			}
		}
		info_6 = info.substr(pos + 3, pos2 - pos);
		int avr_price = stoi(info_6);
		return avr_price;
	}
};
