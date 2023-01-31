#pragma once
#include "Token.h"
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

class Scanner {
	private:
		string input;
		int position;
		int line;
		string value;
		Token currentToken;
	public:
		Scanner(const string& input, int currLine) : input(input), position(0), line(1) {};
		void setLine(int currLine) {
			this->line = currLine++;
		}
		int getLine() {
			return line;
		}
		Token idChecker(string& input) {
			cout << "CheckID" << endl;
			int i = 0;
			for (i; i < input.size(); i++) {
				if (isspace(input.at(i))) break;
			}
			input = input.substr(0,i);
			return Token(ID, input, getLine());
		}
		Token scanToken() {
			cout << "\nIn scantoken\n";
			while(!input.empty() && isspace(input.at(0))) {
				input = input.substr(1);
				cout << "here is" << input << "input";
				position++;
				cout << "in space loop";
			}
			cout << "Leaving space loop ";
			while (!input.empty()) {
				cout << "\n\nin loop\n\n";
				if (input == "EOF") {
					int line = getLine();
					cout << line;
					return Token(EOFILE, "", line);
				}
				if (input.at(0) == ',') {
					TokenType type = COMMA; 
					string value = ",";
					int line = getLine();
					input = input.substr(1);
					return Token(type, value, line);
				}
				// else if (input.at(0) == 'Queries') {
				// 	TokenType type = QUERIES; 
				// 	string value = "Queries";
				// 	int line = getLine();
				// 	input = input.substr(1);
				// 	return Token(type, value, line);
				// }
				else if (input.at(0) == '.') {
					TokenType type = PERIOD; 
					string value = ".";
					int line = getLine();
					input = input.substr(1);
					return Token(type, value, line);
				}
				else if (input.at(0) == '?') {
					TokenType type = Q_MARK; 
					string value = "?";
					int line = getLine();
					input = input.substr(1);
					return Token(type, value, line);
				}
				else if (input.at(0) == '(') {
					TokenType type = LEFT_PAREN; 
					string value = "(";
					int line = getLine();
					input = input.substr(1);
					return Token(type, value, line);
				}
				else if (input.at(0) == ')') {
					TokenType type = RIGHT_PAREN; 
					string value = ")";
					int line = getLine();
					input = input.substr(1);
					return Token(type, value, line);
				}
				else if (input.at(0) == ':') {
					if (input.size() > 1 && input.at(1) == '-') {
						return Token(COLON_DASH, ":-", getLine());
					}
					TokenType type = COLON; 
					string value = ":";
					int line = getLine();
					cout << ":";
					input = input.substr(1);
					cout << "\n." << input.size();
					return Token(type, value, line);
				}
				// else if (input.at(0) == ':-') {
				// 	TokenType type = COLON_DASH; 
				// 	string value = ":-";
				// 	int line = getLine();
				// 	input = input.substr(1);
				// 	return Token(type, value, line);
				// }
				else if (input.at(0) == '*') {
					TokenType type = MULTIPLY; 
					string value = "*";
					int line = getLine();
					input = input.substr(1);
					return Token(type, value, line);
				}
				else if (input.at(0) == '+') {
					TokenType type = ADD; 
					string value = "+";
					int line = getLine();
					input = input.substr(1);
					return Token(type, value, line);
				}
				// else if (input.at(0) == 'Schemes') {
				// 	TokenType type = SCHEMES; 
				// 	string value = "Schemes";
				// 	int line = getLine();
				// 	input = input.substr(1);
				// 	return Token(type, value, line);
				// }
				// else if (input.at(0) == 'Facts') {
				// 	TokenType type = FACTS; 
				// 	string value = "Facts";
				// 	int line = getLine();
				// 	input = input.substr(1);
				// 	return Token(type, value, line);
				// }
				// else if (input.at(0) == 'Rules') {
				// 	TokenType type = RULES; 
				// 	string value = "Rules";
				// 	int line = getLine();
				// 	input = input.substr(1);
				// 	return Token(type, value, line);
				// }
				else if (input.at(0) == '.') { //TODO - Figure this out
					TokenType type = ID; 
					string value = "";
					int line = getLine();
					input = input.substr(1);
					return Token(type, value, line);
				}
				else if (input.at(0) == '\'') { //TODO - Figure this out
							// TokenType type = STRING; 
							// int place = 1;
							// string inputString;
							// while(input.at(place) != '\'') {
							// 	if(input.at(place) == std::string::npos) {
							// 		TokenType type = UNDEFINED;
							// 		int line = getLine();
							// 		input.substr(place);
							// 		value = inputString;
							// 		return Token(type, value, line);
							// 	}
							// 	inputString.push_back(input.at(place));
							// 	place++;
							// }
							// value = inputString;
							// int line = getLine();
							// input.substr(place);
							// return Token(type, value, line);
					cout << "In string type" << endl;
					size_t found = input.find("FALSE_STRING");
					if (found != string::npos) {
						input.clear();
						return Token(UNDEFINED, input, getLine());
					}
				}
				else if (input.at(0) == '#') {

				}
				else if (isalpha(input.at(0))) {
					cout << "In isalpha\n";
					if (input.at(0) == 'Q' && input.substr(0,7) == "Queries") {
						int place = 1;
						string inputString;
						// while (!isalpha(input.at(place))) {
						// 	if (input.at(place,5) == 'u' || 'e' || 'r' || 'i' || 's') {
						// 		inputString.push_back(input.at(place));
						// 		place++;
						// 	}
						// 	else {
						// 		return idChecker(input);
						// 	}
						// }
						inputString = input.substr(0, 7);
						if (inputString != "Queries") {
							cout << inputString << endl;
							return Token(UNDEFINED, inputString, getLine());
						}
						else {
							input.substr(place);
							return Token(QUERIES, inputString, getLine());
						}
					}
					if (input.at(0) == 'R' && input.substr(0,5) == "Rules") {
						//cout << input << " in R";
						int place = 1;
						string inputString;
						// while (!isalpha(input.at(place))) {
						// 	cout << input.at(place) << " ";
						// 	if (input.at(place) == 'u' || 'l' || 'e' || 's') {
						// 		inputString.append(input.at(place), 1);
						// 		place++;
						// 	}
						// 	else {
						// 		return idChecker(input);
						// 	}
						// }
						inputString = input.substr(0, 5);
						if (inputString != "Rules") {
							cout << "!=rules\n";
							cout << inputString;
							return Token(UNDEFINED, inputString, getLine());
						}
						else {
							input.substr(place);
							return Token(RULES, inputString, getLine());
						}
					}
					else if (input.at(0) == 'S' && input.substr(0,7) == "Schemes") {
						int place = 1;
						string inputString;
						// while (!isalpha(input.at(place))) {
						// 	if (input.at(place) == 'c' || 'h' || 'e' || 'm' || 's') {
						// 		inputString.push_back(input.at(place));
						// 		place++;
						// 	}
						// 	else {
						// 		return idChecker(input); // Make ID Checking function
						// 		//return Token(UNDEFINED, inputString, getLine());
						// 	}
						// }
						inputString = input.substr(0, 7);
						if (inputString != "Schemes") {
							return Token(UNDEFINED, inputString, getLine());
						}
						else {
							input.substr(place);
							return Token(SCHEMES, inputString, getLine());
						}
					}
					else if (input.at(0) == 'F' && input.substr(0,5) == "Facts") {
						int place = 1;
						string inputString;
						// while (!isalpha(input.at(place))) {
						// 	if (input.at(place) == 'a' || 'c' || 't' || 's') {
						// 		inputString.push_back(input.at(place));
						// 		place++;
						// 	}
						// 	else {
						// 		return idChecker(input); // Make ID Checking function
						// 		//return Token(UNDEFINED, inputString, getLine());
						// 	}
						// }
						inputString = input.substr(0, 5);
						if (inputString != "Facts") {
							return Token(UNDEFINED, inputString, getLine());
						}
						else {
							input.substr(place);
							return Token(SCHEMES, inputString, getLine());
						}
					}
					else {
						return idChecker(input);
					}
				}
				else if (isdigit(input.at(0))) {
					int i = 0;
					for (i; i < input.size(); i++) {
						if(!isdigit(input.at(i))) break;
					}
					input = input.substr(0,i);
					return Token(UNDEFINED, input, getLine());
				}
				else {
					string inputString = input;
					input.substr(1);
					return Token(UNDEFINED, inputString, getLine());
				}
			}
		}
};
