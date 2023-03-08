#pragma once
#include <string>
#include <set>
#include <sstream>
#include "Scheme.h"
#include "Tuple.h"

class Relation {

    private:

        std::string name;
        Scheme scheme;
        std::set<Tuple> tuples;

    public:
        Relation(const std::string& name, const Scheme& scheme) : name(name), scheme(scheme) { }

        void addTuple(const Tuple& tuple) {
            tuples.insert(tuple);
        }

        std::string toString() const {
            std::stringstream out;
            for (auto& tuple : tuples)
                out << tuple.toString(scheme) << std::endl;
            return out.str();
        }

        Relation select(int index, const std::string& value) const {
            Relation result(name, scheme);
            for (auto& tuple : tuples) {
                if (tuple[index] == value) {
                    result.addTuple(tuple);
                }
            }
            return result;
        }
}; 