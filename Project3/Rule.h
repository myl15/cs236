#pragma once
#include <vector>
#include "Predicate.h"

using namespace std;
class predicate;
class rule {
	private:
		predicate headPredicate;
		vector<predicate> premises;
	public:
		 rule(predicate headPredicate) {
			this->headPredicate = headPredicate;
		 }
		string toString() {
			string answer = "";
			answer += headPredicate.toRuleString();
			answer += " :- ";
			//cout << "|||| " << premises.size() << endl;
			for (unsigned int i=0; i < premises.size(); i++) {
				//cout << "||" << premises.at(i).getParameterSize();
				answer += premises.at(i).toPremiseString();
				answer += premises.at(i).toParameterString();
				if (premises.size() - i == 1) answer += ".";
				else answer += ",";
			}
			return answer;
		}
		void setRuleParam(const vector<Token>& tokens, unsigned int & index) {
			predicate premise(tokens.at(index).getValue());
			//cout << "ASSA" << tokens.at(index).getValue();
			index++; //Get rid of name
			index++; //Get rid of parentheses
			while(tokens.at(index).getType() != RIGHT_PAREN) {
				if (tokens.at(index).getType() == COLON_DASH) index++;
				premise.setRuleParam(tokens.at(index));
				index++; //Get rid of parameter
				if (tokens.at(index).getType() == COMMA) index++; //Get rid of comma/left-paren
				//cout << index << endl;
				if (tokens.at(index).getType() == COLON_DASH) index++;
			}
			if (tokens.at(index).getType() == RIGHT_PAREN) index++;
			premises.push_back(premise);
		}
};