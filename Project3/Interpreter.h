#pragma once

#include <vector>
#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Predicate.h"
using namespace std;
class Interpreter {
	friend class Database;
    private:
        DatalogProgram dp;
        Database db;
    public:
        Interpreter(DatalogProgram dp) : dp(dp) { 
            for (auto& scheme : dp.getSchemes()) {
                Relation newRelation(scheme.getName(), scheme.getParameterNames());
				db.addRelation(newRelation);
            }
			for (auto& tuple : dp.getFacts()) {
				if (db.relations.find(tuple.getName()) != db.relations.end()) {
					db.relations.at(tuple.getName()).addTuple(tuple.getParameterNames());
				}
			}
            

        }


};