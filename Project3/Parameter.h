#pragma once
#include <vector>
#include <string>

using namespace std;
class parameter {
	private:
		std::string name;
		bool isID;
		bool isConstant;
	public:
	parameter(std::string name, bool id) {
		this->name = name;
		this->isID = id;
		if (name[0]=='\'') {
			isConstant = true;
		}
		else {
			isConstant = false;
		}
	}
	std::string toString() {
		return name;
	}
	bool getIsID () {
		return isID;
	}

	bool getIsConstant() {
		return isConstant;
	}

};