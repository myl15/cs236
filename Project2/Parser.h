#pragma once
#include <vector>
#include "Token.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include "Scanner.h"
#include "DatalogProgram.h"

using namespace std;

class Parser {
    private:
        vector<Token> tokens;
		vector<Token> parsedTokens;
    public:
        Parser(const vector<Token>& tokens) : tokens(tokens) {}
        TokenType tokenType() const {
            return tokens.at(0).getType();
        }
		void parse() {
			try {
			realParse();
			}
			catch (Token t) {
				std::cerr << "Failure!" << endl;
				std::cerr<< t.toString();
			}
		}
		void realParse() {
			//cout << "SCHEMES";
			if (tokenType() == SCHEMES) {
				match(SCHEMES);
				match(COLON);
				scheme();
				schemeList();
			}
			else {
				throw tokens.at(0);
			}
		//cout << "FACTS";
			if (tokenType() == FACTS) {
				match(FACTS);
				match(COLON);
				factList();
			}
			else {
				throw tokens.at(0);
			}
//cout << "RULES";
			if(tokenType() == RULES) {
				match(RULES);
				match(COLON);
				ruleList();
			}
			else {
				throw tokens.at(0);
			}
	//cout << "QUERIES";
			if (tokenType() == QUERIES) {
				//cout << "Quereasa f";
				match(QUERIES);
				match(COLON);
				query();
				queryList();
			}
			else {
				throw tokens.at(0);
			}
			//cout << "Creating datalog";
			DatalogProgram dp(parsedTokens);
			//cout << "tostring" << endl;
			cout << dp.toString();
		}
        void advanceToken() {
			parsedTokens.push_back(tokens.at(0));
            tokens.erase(tokens.begin());
        }
        void throwError() {
            std::cerr << "Failure!" << endl;
			std::cerr<< tokens.at(0).toString();
			throw tokens.at(0);
        }
        void match(TokenType t) {
            //std::cout << "match: " << t << endl;
            if (tokenType() == t) {
                advanceToken();
            }
            else throwError();
        }
        void idList() {
            if (tokenType() == COMMA) {
                match(COMMA);
                match(ID);
                idList();
            } 
            else {
                //lambda
            }
        }
        void scheme() {
			match(ID);
			match(LEFT_PAREN);
			match(ID);
			idList();
			match(RIGHT_PAREN);
        }
		void fact () {
			match(ID);
			match(LEFT_PAREN);
			match(STRING);
			stringList();
			match(RIGHT_PAREN);
			match(PERIOD);
		}
		void factList() {
			if (tokenType() == ID && tokens.at(1).getType() == LEFT_PAREN 
				&& tokens.at(2).getType() == STRING) {
				fact();
				factList();
			}
			else {
				//lambda
			}
		}
		void stringList() {
			if (tokenType() == COMMA) {
				match(COMMA);
				match(STRING);
				stringList();
			}
			else {
				//lambda
			}
		}
		void rule() {
			headPredicate();
			match(COLON_DASH);
			predicate();
			predicateList();
			match(PERIOD);
		}
		void ruleList() {
			if (tokenType() == ID) {
				rule();
				ruleList();
			}
			else {
				//lambda
			}
		}
		void headPredicate() {
			match(ID);
			match(LEFT_PAREN);
			match(ID);
			idList();
			match(RIGHT_PAREN);
		}
		void predicate() {
			match(ID);
			match(LEFT_PAREN);
			parameter();
			parameterList();
			match(RIGHT_PAREN);
		}
		void predicateList() {
			if (tokenType() == COMMA) {
				match(COMMA);
				predicate();
				predicateList();
			}
			else {
				//lambda
			}
		}
		void parameter() {
			if (tokenType() == STRING) {
				match(STRING);
			}
			else {
				match(ID);
			}
		}
		void parameterList() {
			if (tokenType() == COMMA) {
				match(COMMA);
				parameter();
				parameterList();
			}
			else {
				//lambda
			}
		}
		void query() {
			predicate();
			match(Q_MARK);
		}
		void queryList() {
			if (tokenType() == ID) {
				query();
				queryList();	
			}
			else {
				//lambda
			}
		}
		void schemeList() {
			if(tokenType() == ID) {
				scheme();
				schemeList();
			}
			else {
				//lambda
			}
		}
};