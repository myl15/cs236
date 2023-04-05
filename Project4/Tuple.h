#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Scheme.h"

using namespace std;
class Tuple : public std::vector<std::string> {

    public:
        Tuple(std::vector<std::string> values) : std::vector<std::string>(values) { }

        std::string toString(const Scheme& scheme) const {
            const Tuple& tuple = *this;
            std::stringstream out;
            for (unsigned int i = 0; i < scheme.size(); i++) {
        
                if (i == scheme.size() - 1) {
                    out << "  " << scheme.at(i) + "=" + tuple.at(i) + "";
                }
                else {
                    out << "  " << scheme.at(i) + "=" + tuple.at(i) + " , ";
                }
                
            }
            
            return out.str();
        }
};