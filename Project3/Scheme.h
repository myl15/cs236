#pragma once
#include <vector>
#include <string>
using namespace std;
class Scheme : public std::vector<std::string> {
    
    public:
        Scheme(std::vector<std::string> names) : std::vector<std::string>(names) { }

};