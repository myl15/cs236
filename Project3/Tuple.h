#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Scheme.h"

class Tuple : public std::vector<std::string> {

    public:
        Tuple(std::vector<std::string> values) : std::vector<std::string>(values) { }

        std::string toString(const Scheme& scheme) const {
            const Tuple& tuple = *this;
            std::stringstream out;
            out << scheme.at(0) + "=" + tuple.at(0) + " , ";
            out << scheme.at(1) + "=" + tuple.at(1) + " , ";
            out << scheme.at(2) + "=" + tuple.at(2) + "";
            return out.str();
        }
};