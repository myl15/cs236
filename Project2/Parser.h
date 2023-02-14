#include <vector>
#include "Token.h"
#include "DatalogProgram.h"

using namespace std;

class Parser {
    private:
        vector<Token> tokens;
    public:
        Parser(const vector<Token>& tokens) : tokens(tokens) {}
        TokenType tokenType() const {
            return tokens.at(0).getType();
        }
		void parse() {
			DatalogProgram d(tokens);
			d.parse();
		}
        void advanceToken() {
            tokens.erase(tokens.begin());
        }
        void throwError() {
            std::cerr << "Failure!" << endl;
			std::cerr<< tokens.at(0).toString();
			exit(0);
        }
        void match(TokenType t) {
            std::cout << "match: " << t << endl;
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
			if (tokenType() == COMMA) {}
		}
};