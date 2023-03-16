#pragma once

#include <map>
#include <vector>
#include <string>
#include "Relation.h"
#include "Tuple.h"
using namespace std;
class Database {
	friend class Interpreter;
    private:
	std::map<std::string, Relation> relations;

	public:
		Database() { }

		void addRelation(Relation newRelation) {
			relations[newRelation.getName()] = newRelation;
		}

		 Relation getRelation(string name) {
		 	return relations.find(name)->second;
		 }

		int getMapSize() {
			return relations.size();
		}

		void printDatabase() {
			for (auto it = relations.cbegin(); it != relations.cend(); ++it) {
				std::cout << "  " << it->second.toString() << " ";
			}
		}
};