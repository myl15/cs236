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
		int tokenCount;
	public:
		Scanner(const string& input, int currLine) : input(input), position(0), line(1) {};
		void setLine(int currLine) {
			this->line = currLine++;
		}
		int getLine() {
			return line;
		}
		void setTokenCount () {
			tokenCount++;
		}
		int getTokenCount () {
			return tokenCount;
		}
		Token idChecker(string& input) {
			//cout << "CheckID" << endl;
			//while (!isspace(input.at(0)) || !isalnum(input.at(0))) {
				//cout << "inspace loop" << endl << endl;
				if (!isspace(input.at(0))) {
					if (isdigit(input.at(0))) {
						//cout << "is digit";
						setTokenCount();
						string undefinedStuff = input.substr(0,1);
						input = input.substr(1);
						return Token(UNDEFINED,undefinedStuff,getLine());
					}
					else if (isalpha(input.at(0))) {
						string returnID;
						while(!isspace(input.at(0)) && isalnum(input.at(0))) {
							//cout << "!isspace";
							returnID = returnID + input.substr(0,1);
							input = input.substr(1);
							//cout << input;
							if (input.empty()) break;
						}
						setTokenCount();
						return Token(ID, returnID, getLine());
					}
					else return Token(UNDEFINED, input, getLine());
				}
			//}
			return Token(UNDEFINED, input, getLine());
		}
		Token scanToken() {
			//cout << "\nIn scantoken\n";
			while(!input.empty() && isspace(input.at(0))) {
				input = input.substr(1);
				//cout << "here is" << input << "input";
				position++;
				//cout << "in space loop";
			}
			//cout << "Leaving space loop ";
			while (!input.empty()) {
				//cout << "\n\nin loop\n\n";
				if (input == "EOF") {
					int line = getLine();
					//cout << line;
					setTokenCount();
					return Token(EOFILE, "", line);
				}
				if (input.at(0) == ',') {
					TokenType type = COMMA; 
					string value = ",";
					int line = getLine();
					input = input.substr(1);
					setTokenCount();
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
					setTokenCount();
					return Token(type, value, line);
				}
				else if (input.at(0) == '?') {
					TokenType type = Q_MARK; 
					string value = "?";
					int line = getLine();
					input = input.substr(1);
					setTokenCount();
					return Token(type, value, line);
				}
				else if (input.at(0) == '(') {
					TokenType type = LEFT_PAREN; 
					string value = "(";
					int line = getLine();
					input = input.substr(1);
					setTokenCount();
					return Token(type, value, line);
				}
				else if (input.at(0) == ')') {
					TokenType type = RIGHT_PAREN; 
					string value = ")";
					int line = getLine();
					input = input.substr(1);
					setTokenCount();
					return Token(type, value, line);
				}
				else if (input.at(0) == ':') {
					if (input.size() > 1 && input.at(1) == '-') {
						setTokenCount();
						return Token(COLON_DASH, ":-", getLine());
					}
					TokenType type = COLON; 
					string value = ":";
					int line = getLine();
					//cout << ":";
					input = input.substr(1);
					//cout << "\n." << input.size();
					setTokenCount();
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
					setTokenCount();
					return Token(type, value, line);
				}
				else if (input.at(0) == '+') {
					TokenType type = ADD; 
					string value = "+";
					int line = getLine();
					input = input.substr(1);
					setTokenCount();
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
					setTokenCount();
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
					//cout << "In string type" << endl;
					size_t found = input.find("FALSE_STRING");
					if (found != string::npos) {
						input.erase(found,13);
						string inputString = input;
						setTokenCount();
						return Token(UNDEFINED, inputString, getLine());
					}
					else {
						setTokenCount();
						return Token(STRING, input, getLine());
					}
				}
				else if (input.at(0) == '#') {
					size_t found = input.find("ERROR_EOF");
					if (found != string::npos) {
						input.erase(found,10);
						string inputString = input;
						//input.clear();
						setTokenCount();
						return Token(UNDEFINED, inputString, getLine());
					}
					//cout << "Making a comment in scanner.h" << endl;
					string newComment = input;
					//input.clear();
					//cout << input << endl;
					setTokenCount();
					return Token(COMMENT, newComment, getLine());
				}
				else if (isalpha(input.at(0))) {
					//cout << "In isalpha\n";
					if (input.at(0) == 'Q' && input.find("Queries") != string::npos) {
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
						//string inputCheck= input.substr(0, 8);
						inputString = input.substr(0,7);
						input = input.substr(7);
						if (!input.empty()) {
							if (isalnum(input.at(0))) {
								//setTokenCount();
								inputString = inputString + input;
								return idChecker(inputString);
							}
							else if (inputString == "Queries") {
								setTokenCount();
								return Token(QUERIES, inputString, getLine());
							}
						}
						else {
							if (inputString == "Queries") {
								setTokenCount();
								return Token(QUERIES, inputString, getLine());
							}
							else {
								inputString = inputString + input;
								return idChecker(inputString);
							}
						}
					}
					else if (input.at(0) == 'R' && input.find("Rules") != string::npos) {
						//cout << input << " in R";
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
						//string inputCheck= input.substr(0, 6);
						inputString = input.substr(0,5);
						input = input.substr(5);
						if (!input.empty()) {
							if (isalnum(input.at(0))) {
								//setTokenCount();
								inputString = inputString + input;
								return idChecker(inputString);
							}
							else if (inputString == "Rules") {
								setTokenCount();
								return Token(RULES, inputString, getLine());
							}
						}
						else {
							if (inputString == "Rules") {
								setTokenCount();
								return Token(RULES, inputString, getLine());
							}
							else {
								inputString = inputString + input;
								return idChecker(inputString);
							}
						}
					}
					else if (input.at(0) == 'S' && input.find("Schemes") != string::npos) {
						string inputString;
						//cout << "Schemey";
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
						//string inputCheck= input.substr(0, 8);
						inputString = input.substr(0,7);
						input = input.substr(7);
						if (!input.empty()) {
							if (isalnum(input.at(0))) {
								//setTokenCount();
								inputString = inputString + input;
								return idChecker(inputString);
							}
							else if (inputString == "Schemes") {
								setTokenCount();
								return Token(SCHEMES, inputString, getLine());
							}
						}
						else {
							if (inputString == "Schemes") {
								setTokenCount();
								return Token(SCHEMES, inputString, getLine());
							}
							else {
								inputString = inputString + input;
								return idChecker(inputString);
							}
						}
					}
					else if (input.at(0) == 'F' && input.find("Facts") != string::npos) {
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
						string inputCheck= input.substr(0, 6);
						inputString = input.substr(0,5);
						input = input.substr(5);
						if (!input.empty()) {
							if (isalnum(input.at(0))) {
								//setTokenCount();
								inputString = inputString + input;
								return idChecker(inputString);
							}
							else if (inputString == "Facts") {
								setTokenCount();
								return Token(FACTS, inputString, getLine());
							}
						}
						else {
							if (inputString == "Facts") {
								setTokenCount();
								return Token(FACTS, inputString, getLine());
							}
							else {
								inputString = inputString + input;
								return idChecker(inputString);
							}
						}
					}
					else {
						return idChecker(input);
					}
				}
				else if (isdigit(input.at(0))) {
					while (isdigit(input.at(0))) {
						//cout << "in digit loop";
					string returnStuff = input.substr(0,1);
					input = input.substr(1);
					setTokenCount();
					return Token(UNDEFINED, returnStuff, getLine());
					}
				}
				else {
					string inputString = input.substr(0,1);
					input = input.substr(1);
					setTokenCount();
					return Token(UNDEFINED, inputString, getLine());
				}
			}
			//cout << "checkycheck";
			string undefinedToken = input.substr(0,1);
			input = input.substr(1);
			setTokenCount();
			return Token(UNDEFINED, undefinedToken, getLine());
		}
};
