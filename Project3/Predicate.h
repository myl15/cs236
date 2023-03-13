#pragma once
#include <vector>
#include <string>
#include "Parameter.h"

using namespace std;
class predicate {
    private:
        string name;
        vector<parameter> parameters;
	public:
		predicate() {};
		predicate(string name) {
			this->name = name;
		}

		string getName() {
			return this->name;
		}
		
		vector<string> getParameterNames() {
			vector <string> result;
			for (auto& parameter : parameters) {
				result.push_back(parameter.toString());
			}
			return result;
		}

		bool getIsID(int index) {
			return parameters.at(index).getIsID();
		}
		void setSchemeParam(Token t) {
			parameter param(t.getValue(), true);
			parameters.push_back(param);
		}
		void setRuleParam(Token t) {
			parameter param(t.getValue(), true);
			//cout <<"\n\n" << t.getValue() << endl;
			parameters.push_back(param);
		}
		void setFactParam(Token t) {
			parameter param(t.getValue(), false);
			parameters.push_back(param);
		}
		string getFactParam(int index) {
			return parameters.at(index).toString();
		}
		int getParameterSize() {
			return parameters.size();
		}
		
		void setQueryParam(Token t) {
			parameter param(t.getValue(), false);
			parameters.push_back(param);
		}
		string toPremiseString() {
			return name;
		}
		string toParameterString() {
			string answer = "(";
			for (unsigned int i = 0; i < parameters.size(); i++) {
				answer += parameters.at(i).toString();
				if (i != parameters.size()-1) answer += ",";
				else answer += ")";
			}
			return answer;
		}
		string toPredicateString() {
			string answer = "";
			//cout << name;
			answer += name;
			answer += "(";
			for (unsigned int i=0; i < parameters.size(); i++) {
				answer += parameters.at(i).toString();
				//cout << parameters.at(i).toString() << endl;
				if (parameters.size() - i > 1) answer += ",";
				if (parameters.size() - i == 1) answer += ")";
			}
			return answer;
		}
		string toString() {
			string answer = "  ";
			answer += name;
			answer += "(";
			for (unsigned int i=0; i < parameters.size(); i++) {
				answer += parameters.at(i).toString();
				if (parameters.size() - i > 1) answer += ",";
				if (parameters.size() - i == 1) answer += ").";
			}
			return answer;
		}
		string toSchemesString() {
			string answer = "  ";
			answer += name;
			answer += "(";
			for (unsigned int i=0; i < parameters.size(); i++) {
				answer += parameters.at(i).toString();
				if (parameters.size() - i > 1) answer += ",";
				if (parameters.size() - i == 1) answer += ")";
			}
			return answer;
		}
		string toQueryString() {
			string answer = "  ";
			answer += name;
			answer += "(";
			for (unsigned int i=0; i < parameters.size(); i++) {
				answer += parameters.at(i).toString();
				if (parameters.size() - i > 1) answer += ",";
				if (parameters.size() - i == 1) answer += ")?";
			}
			return answer;
		}
		string toRuleString() {
			string answer = "  ";
			answer += name;
			answer += "(";
			for (unsigned int i=0; i < parameters.size(); i++) {
				answer += parameters.at(i).toString();
				if (parameters.size() - i > 1) answer += ",";
				if (parameters.size() - i == 1) answer += ")";
			}
			return answer;
		}
};
		