#pragma once
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
enum TokenType {
	COMMA, PERIOD, Q_MARK, MULTIPLY, STRING, ADD,
	SCHEMES, COLON, FACTS, LEFT_PAREN, RULES, COMMENT, 
	QUERIES, ID, RIGHT_PAREN,
	UNDEFINED, COLON_DASH, EOFILE
};

class Token {
	private:
		TokenType type;
		string value;
		int line;
	public:
		Token() {};
		Token(TokenType type, string value, int line) : 
		type(type), value(value), line(line) {};
		//This function creates a string with token info
		string toString() const {
			stringstream out;
			out << "(" << typeName(type) << "," << "\"" << value << "\"" <<  "," << line << ")";
			return out.str();
		}
		string getValue() const {
			return value;
		}
		TokenType getType() const {
			return type;
		}
		//This function returns the name of the Token
		string typeName(TokenType type) const {
			switch(type){
				case 0:
					return "COMMA";
				case 1:
					return "PERIOD";
				case 2:
					return "Q_MARK";
				case 3:
					return "MULTIPLY";
				case 4:
					return "STRING";
				case 5:
					return "ADD";
				case 6:
					return "SCHEMES";
				case 7:
					return "COLON";
				case 8:
					return "FACTS";
				case 9:
					return "LEFT_PAREN";
				case 10:
					return "RULES";
				case 11:
					return "COMMENT";
				case 12:
					return "QUERIES";
				case 13:
					return "ID";
				case 14:
					return "RIGHT_PAREN";
				case 15:
					return "UNDEFINED";
				case 16:
					return "COLON_DASH";
				case 17:
					return "EOF";
			}
			return "UNDEFINED";
		}
};
