#pragma once
#include <vector>
#include <string>

using namespace std;
class parameter {
	private:
		std::string name;
		bool isID;
	public:
	parameter(std::string name, bool id) {
		this->name = name;
		this->isID = id;
	}
	std::string toString() {
		return name;
	}
	bool getIsID () {
		return isID;
	}

};