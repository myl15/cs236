#include <vector>
#include <sstream>
#include <iostream>
#include "Scanner.h"
#include "Token.h"
#include <string>
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include <set>

class DatalogProgram {
	private:
		vector<Predicate> schemes;
		vector<Predicate> facts;
		vector<Rule> rules;
		vector<Predicate> queries;
	public:
		string toString() {
			stringstream out;
			out << "Success!" << endl;
			out << "Schemes(" << schemes.size() << ") :" << endl;
			for (Predicate curr : schemes) {
				out << curr << endl;
			}
			out << "Facts(" << facts.size() << ") :" << endl;
			for (Predicate curr : facts) {
				out << curr << endl;
			}
			out << "Rules(" << rules.size() << ") :" << endl;
			for (Rule curr : rules) {
				out << curr << endl;
			}
			out << "Queries(" << queries.size() << ") :" << endl;
			for (Predicate curr : queries) {
				out << curr << endl;
			}

		}
		set<String> createDomain(vector<Predicate> facts) {
			set<String> domain;
			for (Predicate curr : facts) {
				
			}
			return domain;
		}
		void parse() {
			match(SCHEME)
		}
};