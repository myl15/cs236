#pragma once

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


using namespace std;
class DatalogProgram {
	friend class Parser;
	private:
		unsigned int index = 0;
		vector<predicate> schemes;
		vector<predicate> facts;
		vector<rule> rules;
		vector<predicate> queries;
		set<string> domains;
	public:
		DatalogProgram() { }
		DatalogProgram(const vector<Token>& tokens) {
			//predicate pred(tokens);
			//cout << "Scheme check\n\n";
			if (tokens.at(index).getType() == SCHEMES) index++;
			if (tokens.at(index).getType() == COLON) index++;
			while (tokens.at(index).getType() != FACTS) {
				predicate pred(tokens.at(index).getValue());
				index++; //Get rid of name
				index++; //Get rid of parentheses
				if (TokenType() == RIGHT_PAREN) throw tokens.at(0);
				while(tokens.at(index).getType() != RIGHT_PAREN) {
					pred.setSchemeParam(tokens.at(index));
					index++; //Get rid of parameter
					if (tokens.at(index).getType() == COMMA) index++; //Get rid of comma/left-paren
					//cout << index << endl;
				}
				if (tokens.at(index).getType() == RIGHT_PAREN) index++;
				schemes.push_back(pred);
			}
			//cout << index << " - Fact check\n\n";
			if (tokens.at(index).getType() == FACTS) index++;
			//cout << "1\n";
			if (tokens.at(index).getType() == COLON) index++;
			//cout << "2\n";
			while (tokens.at(index).getType() != RULES) {
				//cout << index <<"\n";
				predicate pred(tokens.at(index).getValue());
				index++; //Get rid of name
				index++; //Get rid of parentheses
				if (TokenType() == RIGHT_PAREN) throw tokens.at(0);
				while (tokens.at(index).getType() != PERIOD) {
					
					pred.setFactParam(tokens.at(index));
					index++; //Get rid of parameter
					index++; //Get rid of comma/left-paren
					
				}
				if (tokens.at(index).getType() == PERIOD) index++;
				facts.push_back(pred);
			}
			//cout << "Rule check\n\n" << index;
			if (tokens.at(index).getType() == RULES) index++;
			//cout << tokens.at(index).getValue() << endl;
			if (tokens.at(index).getType() == COLON) index++;
			//cout << tokens.at(index).getType() << endl;
			while (tokens.at(index).getType() != QUERIES) {
				//cout << "IN WHILE LOOP";
				//cout << tokens.at(index).getValue() << endl;
				predicate headPredicate(tokens.at(index).getValue()); 
				index++; //Get rid of name
				index++; //Get rid of parentheses
				if (TokenType() == RIGHT_PAREN) throw tokens.at(0);
				while(tokens.at(index).getType() != RIGHT_PAREN) {
					//cout << tokens.at(index).getValue() << endl;
					headPredicate.setRuleParam(tokens.at(index));
					index++; //Get rid of parameter
					if (tokens.at(index).getType() == COMMA) index++; //Get rid of comma/left-paren
					//cout << index << endl;
				}
				rule rul(headPredicate);
				if (tokens.at(index).getType() == RIGHT_PAREN) index++;
				if (tokens.at(index).getType() == COLON_DASH) index++;
				//cout << tokens.at(index).getType() << endl;
				while (tokens.at(index).getType() != PERIOD) {
					//cout << tokens.at(index).getValue() <<  "1" << endl;
					if (tokens.at(index).getType() == COMMA) index++;
					rul.setRuleParam(tokens, index);
					//index++; //Get rid of parameter
					//cout << "ASASFA" << tokens.at(index).getValue() << "2" << endl;
					if (tokens.at(index).getType() == COMMA) index++; //Get rid of comma/left-paren
					
					if (tokens.at(index).getType() == COLON_DASH) index++;
				}
				//cout << "OUT OF WHILE LOOP" << tokens.at(index).getValue();
				if (tokens.at(index).getType() == RIGHT_PAREN) index++;
				if (tokens.at(index).getType() == PERIOD ) index++;
				//cout << tokens.at(index).getValue();
				rules.push_back(rul);
			}
			//cout << "Query check\n\n" << index;
			//cout << tokens.at(index).toString() << endl;
			if (tokens.at(index).getType() == QUERIES) index++;
			//cout << tokens.at(index).toString() << endl;
			if (tokens.at(index).getType() == COLON) index++;

			while (index < (tokens.size()-1)) {
			//	cout << "IN WHILE LOOP";
				predicate pred(tokens.at(index).getValue());
				index++; //Get rid of name
				index++; //Get rid of parentheses
				if (TokenType() == RIGHT_PAREN) throw tokens.at(0);
				//cout << tokens.at(index).toString() << endl;
				while (tokens.at(index).getType() != Q_MARK) {
					//cout << tokens.at(index).toString() << endl;
					
					//cout << tokens.at(index).toString() << endl;
					pred.setQueryParam(tokens.at(index));
					index++; //Get rid of parameter
					index++; //Get rid of comma/left-paren
					//cout << tokens.at(index).toString() << endl;
					
				}
				queries.push_back(pred);
				index++; // Get rid of question mark
			}
			domains = createDomain(facts);
		}

		vector<predicate> getSchemes() {
			return this->schemes;
		}

		vector<predicate> getFacts() {
			return this->facts;
		}

		vector<predicate> getQueries() {
			return this->queries;
		}
		

		string toString() {
			stringstream out;
			out << "Success!" << endl;
			out << "Schemes(" << schemes.size() << "):" << endl;
			for (predicate curr : schemes) {
				out << curr.toSchemesString() << endl;
			}
			out << "Facts(" << facts.size() << "):" << endl;
			for (predicate curr : facts) {
				out << curr.toString() << endl;
			}
			out << "Rules(" << rules.size() << "):" << endl;
			for (rule curr : rules) {
				out << curr.toString() << endl;
			}
			out << "Queries(" << queries.size() << "):" << endl;
			for (predicate curr : queries) {
				out << curr.toQueryString() << endl;
			}
			out << "Domain(" << domains.size() << "):" << endl;
			set<string>::iterator itr;
			for (itr = domains.begin(); itr != domains.end(); itr++) {
				out << "  " << *itr  << endl;
			}
			return out.str();
		}
		set<string> createDomain(vector<predicate> facts) {
			set<string> domain;
			for (predicate curr : facts) {
				for (int i =0; i < curr.getParameterSize(); i++) {
					domain.insert(curr.getFactParam(i));
				}
			}
			return domain;
		}
// 		void parse() {
// 			if (tokenType() == SCHEMES) {
// 				match(SCHEMES);
// 				match(COLON);
// 				scheme();
// 				schemeList();
// 			}
// 			else {
// 				throw t.at(0);
// 			}

// 			if (tokenType() == FACTS) {
// 				match(FACTS);
// 				match(COLON);
// 				factList();
// 			}
// 			else {
// 				throw tokens.at(0);
// 			}

// 			if(tokenType() == RULES) {
// 				match(RULES);
// 				match(COLON);
// 				ruleList();
// 			}
// 			else {
// 				throw tokens.at(0);
// 			}

// 			if (tokenType() == QUERIES) {
// 				match(QUERIES);
// 				match(COLON);
// 				query();
// 				queryList();
// 			}
// 			else {
// 				throw tokens.at(0);
// 			}
// 		}
};