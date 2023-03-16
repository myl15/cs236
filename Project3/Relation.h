#pragma once
#include <string>
#include <set>
#include <sstream>
#include <vector>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;
class Relation {

    private:

        std::string name;
        Scheme scheme;
        std::set<Tuple> tuples;

    public:
        Relation() { }
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

        Relation selectOne(int index, const std::string& value) const {
            Relation result(name, scheme);
            for (auto& tuple : tuples) {
                if (tuple[index] == value) {
                    result.addTuple(tuple);
                }
            }
            return result;
        }

        Relation selectTwo(int index1, int index2) const {
            Relation result(name, scheme);
            for (auto& tuple : tuples) {
                if (tuple[index1] == tuple[index2]) {
                    result.addTuple(tuple);
                }
            }
            return result;
        }

        Relation project(map<string, int> Queries, vector<string> vars_order) const{
            
            Relation result(name, scheme);

            for (auto& tuple : tuples) {
                vector<string> projectedTuple;
                vector<string> tuple_values;
                for (unsigned int i = 0; i < vars_order.size(); i++) {
                    int index = Queries.at(vars_order.at(i));
                    projectedTuple.push_back(tuple[index]);
                }
                result.addTuple(projectedTuple);
            }     
            
            return result;
        }

        Relation rename(Relation rel, vector<string> order) const {  
            Scheme newScheme(order);
            Relation result = rel;
            result.scheme = newScheme;
            //result.addTuple();
            return result;
        }

		std::string getName() {
			return this->name;
		}

        set<Tuple> getTuples() {
            return this->tuples;
        }

        int getTupleSize() {
            return tuples.size();
        }
}; 