#pragma once
#include <vector>
#include <string>

class parameter {
	private:
		string name;
		bool isID;
	public:
	parameter(string name, bool id) {
		this->name = name;
		this->isID = id;
	}
	string toString() {
		return name;
	}
	bool getIsID () {
		return isID;
	}

};