#pragma once

#include <vector>
#include <map>
#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Predicate.h"
using namespace std;
class Interpreter {
	friend class Database;
    friend class Predicate;
    friend class Relation;
    friend class Parameter;
    private:
        DatalogProgram dp;
        Database db;
        vector<Relation> solvedQueries;
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
            
            vector<predicate> Queries = dp.getQueries();
            evaluateAllQueries(Queries);
            /*for (auto& query : dp.getQueries()) {
                evaluateQuery(query);
            }*/
            db.printDatabase();

        }
        void evaluateAllQueries(vector<predicate> Queries) {
            for (unsigned int i = 0; i < Queries.size(); i++) {
                string name = Queries.at(i).getName();
                vector<string> query = Queries.at(i).getParameterNames();

                cout << name << "(";
                for (unsigned int j = 0; j < query.size(); j++) {
                    cout << query.at(j);
                    if (j < query.size() - 1) cout << ',';
                    else cout << ")?";
                }
                solvedQueries.push_back(evaluateQuery(Queries.at(i)));
            }
        }

        Relation evaluateQuery(predicate p) {
            //Grab relation from database
            map<string, int> Queries;
            vector<string> nonAlphaQueries;

            Relation queryRelation = db.getRelation(p.getName());
            //Go through the parameters
            int index = 0;
            for (auto& parameter : p.getParameters()) {
                //Insert variable name into map and vector
                //Queries.insert(make_pair(parameter.toString(), index));
                
                /*nonAlphaQueries.push_back(parameter.toString());*/
                //Do a select for each constant
                if (parameter.getIsConstant()) {
                   queryRelation = queryRelation.selectOne(index, parameter.toString());
                  
                }
                else {
                    if (Queries.find(parameter.toString()) != Queries.end()) {
                        //Run select two
                        queryRelation = queryRelation.selectTwo(index, Queries.find(parameter.toString())->second);
                        
                    }
                    else {
                        Queries.insert(make_pair(parameter.toString(), index));
                        nonAlphaQueries.push_back(parameter.toString());
                    }
                }
                //cout << queryRelation.toString() << endl << endl;
                index++;
            }
            if (queryRelation.getTupleSize() != 0) {
                cout << "Yes(" << queryRelation.getTupleSize() << ")" << endl;
            }
            else cout << "No" << endl;

            queryRelation = queryRelation.project(Queries, nonAlphaQueries);
            //cout << queryRelation.toString() << endl << endl;

            queryRelation = queryRelation.rename(queryRelation, nonAlphaQueries);
            //cout << queryRelation.toString() << endl << endl;

            return queryRelation;
        }

};