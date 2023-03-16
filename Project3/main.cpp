#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
//#include "DatalogProgram.h"
#include "Interpreter.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void CommentAndStringCheck(string& inputLine, ifstream& input, int& line, int& tokenCount, vector<Token>& tokens);
string GetRidOfWhitespace(string& inputLine);

int main(int argc, char* argv[]) {
	string filename = argv[1];
	
	ifstream input(filename);
	if (!input.is_open()) {
		std::cout << "Error opening file";
		exit(0);
	}
	//ofstream output ("output.txt");
	string inputLine;
	string endOfFile = "EOF";
	string currValue;
	int tokenCount = 0;
	int line = 0;
	vector<Token> tokens;
	while (!input.eof() || input.eof()) {
		//cout << "\nSize:" << inputLine.size() << inputLine;
		if (input.eof()) {
			//cout << "ENDOFFILE" << endl;
			//line++;
			Scanner myScanner(endOfFile, line);
			myScanner.setLine(line);
			Token t = myScanner.scanToken();
			//std::cout << t.toString() << endl;
			tokenCount++;
			tokens.push_back(t);
			//std::cout << "Total Tokens = " << tokenCount << endl;
			break;
		}
		if (inputLine.empty()) {
			//std::cout << "Getline1 ";
			inputLine = "";
			getline(input, inputLine);
			//std::cout << "got the line";
			line++;
		}
		else {
			size_t i = inputLine.find(currValue);
			if (i != string::npos) {
				inputLine.erase(i, currValue.length());
				//std::cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
			}
		}
		// if(inputLine.size() == 0 || inputLine == "") {
		// 	//std::cout << "Getline2 ";
		// 	inputLine = "";
		// 	getline(input, inputLine);
		// 	//std::cout << "New line = " << inputLine;
		// 	line++;
		// }
		while (!inputLine.empty()) {
			//Get rid of whitespace
			//std::cout << "\n in the new loop";
			inputLine = GetRidOfWhitespace(inputLine);

			/*
				Check for Comments and Strings
			*/
			//std::cout << "\n Yup"  << inputLine << "yeet" << endl;
			if (!inputLine.empty()) CommentAndStringCheck(inputLine, input, line, tokenCount, tokens);
			/*
				Initialize scanner and tokens
			*/
			if (!inputLine.empty()) {
				//std::cout << "making scanner";
				Scanner myScanner(inputLine, line);
				//std::cout << "made scanner";
				myScanner.setLine(line);
				//std::cout << "setline";
				Token t = myScanner.scanToken();
				//std::cout << "made token";
				currValue = t.getValue();
				//std::cout << "setvalue";
				//std::cout << t.toString() << endl;
				tokenCount++;
				tokens.push_back(t);
				std::string::size_type i = inputLine.find(currValue);
				if (i != std::string::npos) {
					//std::cout << "Currvalue " << currValue << endl;
					inputLine.erase(i, currValue.length());
					//std::cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
				}
			}
		}
	}
	//std::cout << "Begin Parsing";

	Parser p = Parser(tokens);
	p.parse();

	Interpreter i = Interpreter(p.getDp());


	/* std::cout << "\n\\Beginning SCANNING\\" << endl;
	Scanner s = Scanner(" ,,");
	Token t= s.scanToken();
	std::cout << t.toString() << endl; */
}

string GetRidOfWhitespace(string& inputLine) {
	//Get rid of whitspace
	inputLine.erase(0, inputLine.find_first_not_of(" \t\n\r"));
	//std::cout << "got rid of whitey\n";
	return inputLine;
}

void CommentAndStringCheck(string& inputLine, ifstream& input, int& line, int& tokenCount, vector<Token>& tokens) {
	string endOfFile = "EOF";
	string currValue;
	bool foundComment = false;
	bool foundString = false;
	int stringLine = line;
	inputLine = GetRidOfWhitespace(inputLine);
	//std::cout << inputLine << "----";
	//std::cout << "asdasd" << inputLine.at(0);
	if (inputLine.at(0) == '\'' && inputLine.size() > 1) {
		string inputString;
		//std::cout << "instrng\n";
		inputString = inputString + inputLine.substr(0, 1);
		inputLine = inputLine.substr(1);
		while (!foundString) {
			size_t found = inputLine.find("\'\'");
			//std::cout << "Found \'";
			if (found != string::npos) {
				size_t found2 = inputLine.substr(0, found).find('\'');
				if (found2 != string::npos) {
					inputString = inputString + inputLine.substr(0, found2 + 1);
					inputLine = inputLine.substr(found2 + 1);
					Scanner myScanner(inputString, line);
					myScanner.setLine(stringLine);
					Token t = myScanner.scanToken();
					tokenCount++;
					tokens.push_back(t);
					currValue = t.getValue();
					//std::cout << t.toString() << endl;
					foundString = true;
					if (!inputLine.empty()) CommentAndStringCheck(inputLine, input, line, tokenCount, tokens);
					break;
				}
				// string emptyStringCheck = inputLine.substr(0,found+2);
				// if (emptyStringCheck.size() == 2) {
				// 	Scanner myScanner(emptyStringCheck, line);
				// 	myScanner.setLine(line);
				// 	Token t = myScanner.scanToken();
				// 	tokenCount++;
				// 	currValue = t.getValue();
				// 	std::cout << t.toString() << endl;
				// 	foundString = true;
				// }
				// while(emptyStringCheck.at(0) != '\'') {
				// 	emptyStringCheck = emptyStringCheck.substr(1);
				// }
				//string inputString;
				inputString = inputString + inputLine.substr(0, found + 2);
				//std::cout << "  " << inputString << endl;
				inputLine = inputLine.substr(found + 2);
				//std::cout << "NEW INPUTLINE - " << inputLine << endl;
				found = inputLine.find('\'');
				if (found != string::npos) {
					inputString = inputString + inputLine.substr(0, found + 1);
					//std::cout << "THIS is inputstring" << inputString << endl << endl;
					inputLine = inputLine.substr(found + 1);
					Scanner myScanner(inputString, stringLine);
					myScanner.setLine(stringLine);
					Token t = myScanner.scanToken();
					tokenCount++;
					tokens.push_back(t);
					currValue = t.getValue();
					//std::cout << t.toString() << endl;
					foundString = true;
					size_t i = inputLine.find(currValue);
					if (i != string::npos) {
						inputLine.erase(i, currValue.length());
						//std::cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
						for (unsigned int i = 0; i < inputLine.size(); i++) {
							if (isspace(inputLine.at(i))) inputLine = inputLine.substr(1);
							//std::cout << i << " ";
						}
					}
					if (!inputLine.empty()) CommentAndStringCheck(inputLine, input, line, tokenCount, tokens);
					break;
				}
				else if (!input.eof() || !inputLine.empty()) {
					//std::cout << "!eof" << endl;
					inputString = inputString + inputLine + "\n";
					inputLine.clear();
					getline(input, inputLine);
					line++;
					//std::cout << "\n" << inputLine;
				}
				else {
					//std::cout << "FALSESTRING" << endl;
					inputString = inputString + "FALSE_STRING";
					//std::cout << inputString;
					Scanner myScanner(inputString, stringLine);
					myScanner.setLine(stringLine);
					Token t = myScanner.scanToken();
					tokenCount++;
					tokens.push_back(t);
					currValue = t.getValue();
					//std::cout << t.toString() << endl;
					foundString = true;
					size_t i = inputLine.find("\'" + currValue);
					if (i != string::npos) {
						inputLine.erase(i, currValue.length());
						//std::cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
						for (unsigned int i = 0; i < inputLine.size(); i++) {
							if (isspace(inputLine.at(i))) inputLine = inputLine.substr(1);
							//std::cout << i << " ";
						}
					}
					if (!inputLine.empty()) CommentAndStringCheck(inputLine, input, line, tokenCount, tokens);
					break;
				}
			}
			found = inputLine.find('\'');
			if (found != string::npos) {
				inputString = inputString + inputLine.substr(0, found + 1);
				inputLine = inputLine.substr(found + 1);
				//std::cout << "\n" << inputLine;
				//inputLine.clear();
				Scanner myScanner(inputString, line);
				myScanner.setLine(stringLine);
				Token t = myScanner.scanToken();
				tokenCount++;
				tokens.push_back(t);
				currValue = t.getValue();
				//std::cout << t.toString() << endl;
				foundString = true;
				size_t i = inputLine.find('\'' + currValue);
				if (i != string::npos) {
					inputLine.erase(i, currValue.length());
					//std::cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
					for (unsigned int i = 0; i < inputLine.size(); i++) {
						if (isspace(inputLine.at(i))) inputLine = inputLine.substr(1);
						//std::cout << i << " ";
					}
				}
				if (!inputLine.empty()) CommentAndStringCheck(inputLine, input, line, tokenCount, tokens);
				break;
			}
			else if (!input.eof() || !inputLine.empty()) {
				//std::cout << "!eof " << inputString << endl;
				inputString = inputString + inputLine + "\n";
				//inputLine.clear();
				getline(input, inputLine);
				line++;
			}
			else {
				inputString = inputString + "FALSE_STRING";
				//std::cout << inputString;
				Scanner myScanner(inputString, line);
				myScanner.setLine(stringLine);
				Token t = myScanner.scanToken();
				tokenCount++;
				tokens.push_back(t);
				currValue = t.getValue();
				//std::cout << t.toString() << endl;
				foundString = true;
				size_t i = inputLine.find("\'" + currValue);
				if (i != string::npos) {
					inputLine.erase(i, currValue.length());
					//std::cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
				}
				if (!inputLine.empty()) CommentAndStringCheck(inputLine, input, line, tokenCount, tokens);
				break;
			}
			// 	else if (!input.eof() || !inputLine.empty()) {
			// 		//std::cout << "!eof" << endl;
			// 		inputString = inputString + inputLine;
			// 		inputLine.clear();
			// 		getline(input, inputLine);
			// 		line++;
			// 		//std::cout << "\nnewINput " << inputLine << endl;
			// 	}
			// 	else {
			// 		inputString = inputString + "FALSE_STRING";
			// 			//std::cout << inputString;
			// 			Scanner myScanner(inputString, line);
			// 			myScanner.setLine(line);
			// 			Token t = myScanner.scanToken();
			// 			tokenCount++;
			// 			currValue = t.getValue();
			// 			std::cout << t.toString() << endl;
			// 			foundString = true;
			// 			size_t i = inputLine.find("\'"+currValue);
			// 			if (i != string::npos) {
			// 				inputLine.erase(i, currValue.length());
			// 				//std::cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
			// 			}
			// 			if (!inputLine.empty()) CommentAndStringCheck(inputLine, input,  line, tokenCount);
			// 			break;
			// 	}
		}
	}
	else if (inputLine.at(0) == '#' && inputLine.size() > 1) {
		//std::cout << "in comment section";
		size_t found = inputLine.find("#|");
		//cout << "DIDNT FIND IT";
		if (found != string::npos) {
			//std::cout <<"FOUND #| " << endl;
			//cout << inputLine;
			string finalInput = inputLine.substr(0, found + 2);
			inputLine = inputLine.substr(found + 2);
			//cout << "Entering while loop" << endl;
			while (!foundComment) {
				string newInput;
				getline(input, newInput);
				inputLine = inputLine + newInput;
				found = inputLine.find("#|");
				if (found != string::npos) {
					foundComment = true;
					finalInput = finalInput + inputLine;
					inputLine = inputLine.substr(found + 2);
					Scanner myScanner(finalInput, line);
					myScanner.setLine(line);
					Token t = myScanner.scanToken();
					//tokenCount++;
					//tokens.push_back(t);
					currValue = t.getValue();
					//std::cout << t.toString() << endl;
					size_t i = inputLine.find("#|" + currValue);
					if (i != string::npos) {
						inputLine.erase(i, currValue.length());
						//std::cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
					}
					if (!inputLine.empty()) CommentAndStringCheck(inputLine, input, line, tokenCount, tokens);
				}
				else if (input.eof()) {
					//std::cout << "found eof" << endl;
					finalInput = finalInput + inputLine + "ERROR_EOF";
					Scanner myScanner(finalInput, line);
					myScanner.setLine(line);
					Token t = myScanner.scanToken();
					//tokenCount++;
					//tokens.push_back(t);
					currValue = t.getValue();
					//std::cout << t.toString() << endl;
					foundComment = true;
					inputLine.clear();
					size_t i = inputLine.find("#|" + currValue);
					if (i != string::npos) {
						inputLine.erase(i, currValue.length());
						//std::cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
					}
					if (!inputLine.empty()) CommentAndStringCheck(inputLine, input, line, tokenCount, tokens);
				}
			}
		}
		else {
			foundComment = true;
			//std::cout << "FOUNDCOMMENT " << endl;
			Scanner myScanner(inputLine, line);
			//cout << "MADE SCANNER";
			myScanner.setLine(line);
			//cout << "SETLINE";
			Token t = myScanner.scanToken();
			//cout << "SCANNED TOKEN";
			//tokenCount++;
			//tokens.push_back(t);
			currValue = t.getValue();
			//std::cout << t.toString() << endl;

			size_t i = inputLine.find(currValue);
			if (i != string::npos) {
				inputLine.erase(i, currValue.length());
				//std::cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
			}
			if (!inputLine.empty()) CommentAndStringCheck(inputLine, input, line, tokenCount, tokens);
		}
	}

	//  vector<Token> tokens = {
	//   Token(COMMA,",",2),
	//   Token(ID,"Ted",2),
	//   Token(COMMA,",",2),
	//   Token(ID,"Zed",2),
	//   Token(RIGHT_PAREN,")",2),
	// };

	// Parser p = Parser(tokens);
	// p.idList();
}