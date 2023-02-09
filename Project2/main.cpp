#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void CommentAndStringCheck(string& inputLine, ifstream& input, int& line, int& tokenCount);
string GetRidOfWhitespace(string& inputLine);

int main (int argc, char* argv[]) {
// 	string filename = argv[1];
// 	ifstream input (filename);
// 	if (!input.is_open()) {
// 		cout << "Error opening file";
// 		exit(0);
// 	}
// 	//ofstream output ("output.txt");
// 	string inputLine;
// 	string endOfFile = "EOF";
// 	string currValue;
// 	int tokenCount = 0;
// 	int line = 0;
// 	while ( !input.eof() || input.eof() ) {
// 		//cout << "\nSize:" << inputLine.size() << inputLine;
// 		if (input.eof()) {
// 			//cout << "ENDOFFILE" << endl;
// 			//line++;
// 			Scanner myScanner(endOfFile, line);
// 			myScanner.setLine(line);
// 			Token t = myScanner.scanToken();
// 			cout << t.toString() << endl;
// 			tokenCount++;
// 			cout << "Total Tokens = " << tokenCount << endl;
// 			break;
// 		}
// 		if(inputLine.empty()) {
// 			//cout << "Getline1 ";
// 			inputLine = "";
// 			getline(input, inputLine);
// 			//cout << "got the line";
// 			line++;
// 		}
// 		else {
// 			size_t i = inputLine.find(currValue);
// 			if (i != string::npos) {
//    				inputLine.erase(i, currValue.length());
// 				//cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
// 			}
// 		}
// 		// if(inputLine.size() == 0 || inputLine == "") {
// 		// 	//cout << "Getline2 ";
// 		// 	inputLine = "";
// 		// 	getline(input, inputLine);
// 		// 	//cout << "New line = " << inputLine;
// 		// 	line++;
// 		// }
// 		while (!inputLine.empty()) {
// 			//Get rid of whitespace
// 			//cout << "\n in the new loop";
// 			inputLine = GetRidOfWhitespace(inputLine);

// 			/*
// 				Check for Comments and Strings
// 			*/
// 			//cout << "\n Yup"  << inputLine << "yeet" << endl;
// 			if (!inputLine.empty()) CommentAndStringCheck(inputLine, input, line, tokenCount);
// 			/* 
// 				Initialize scanner and tokens
// 			*/
// 			 if (!inputLine.empty()) {
// 				//cout << "making scanner";
// 				Scanner myScanner(inputLine, line);
// 				//cout << "made scanner";
// 				myScanner.setLine(line);
// 				//cout << "setline";
// 				Token t = myScanner.scanToken();
// 				//cout << "made token";
// 				currValue = t.getValue();
// 				//cout << "setvalue";
// 				cout << t.toString() << endl;
// 				tokenCount++;
// 				std::string::size_type i = inputLine.find(currValue);
// 				if (i != std::string::npos) {
// 					//cout << "Currvalue " << currValue << endl;
// 					inputLine.erase(i, currValue.length());
// 					//cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
// 				}
// 			}
// 		}
// 	}
	
// 	/* cout << "\n\\Beginning SCANNING\\" << endl;
// 	Scanner s = Scanner(" ,,");
// 	Token t= s.scanToken();
// 	cout << t.toString() << endl; */
// }

// string GetRidOfWhitespace(string& inputLine) {
// 	//Get rid of whitspace
// 	inputLine.erase(0, inputLine.find_first_not_of(" \t\n\r"));
// 	//cout << "got rid of whitey\n";
// 	return inputLine;
// }

// void CommentAndStringCheck (string& inputLine, ifstream& input, int& line, int& tokenCount) {
// 	string endOfFile = "EOF";
// 	string currValue;
// 	bool foundComment = false;
// 	bool foundString = false;
// 	int stringLine = line;
// 	inputLine = GetRidOfWhitespace(inputLine);
// 	//cout << inputLine << "----";
// 	//cout << "asdasd" << inputLine.at(0);
// 	if (inputLine.at(0) == '\'' &&   inputLine.size() > 1) {
// 		string inputString;
// 		//cout << "instrng\n";
// 		inputString = inputString + inputLine.substr(0,1);
// 		inputLine = inputLine.substr(1);
// 		while (!foundString) {
// 			size_t found = inputLine.find("\'\'");
// 			//cout << "Found \'";
// 			if(found != string::npos) {
// 				size_t found2 = inputLine.substr(0,found).find('\'');
// 				if (found2 != string::npos) {
// 					inputString = inputString + inputLine.substr(0,found2+1);
// 					inputLine = inputLine.substr(found2+1);
// 					Scanner myScanner(inputString, line);
// 					myScanner.setLine(stringLine);
// 					Token t = myScanner.scanToken();
// 					tokenCount++;
// 					currValue = t.getValue();
// 					cout << t.toString() << endl;
// 					foundString = true;
// 					if(!inputLine.empty()) CommentAndStringCheck(inputLine, input,  line, tokenCount);
// 					break;
// 				}
// 				// string emptyStringCheck = inputLine.substr(0,found+2);
// 				// if (emptyStringCheck.size() == 2) {
// 				// 	Scanner myScanner(emptyStringCheck, line);
// 				// 	myScanner.setLine(line);
// 				// 	Token t = myScanner.scanToken();
// 				// 	tokenCount++;
// 				// 	currValue = t.getValue();
// 				// 	cout << t.toString() << endl;
// 				// 	foundString = true;
// 				// }
// 				// while(emptyStringCheck.at(0) != '\'') {
// 				// 	emptyStringCheck = emptyStringCheck.substr(1);
// 				// }
// 				//string inputString;
// 				inputString = inputString + inputLine.substr(0,found+2);
// 				//cout << "  " << inputString << endl;
// 				inputLine = inputLine.substr(found+2);
// 				//cout << "NEW INPUTLINE - " << inputLine << endl;
// 				found = inputLine.find('\'');
// 				if (found != string::npos) {
// 					inputString = inputString + inputLine.substr(0,found+1);
// 					//cout << "THIS is inputstring" << inputString << endl << endl;
// 					inputLine = inputLine.substr(found+1);
// 					Scanner myScanner(inputString, stringLine);
// 					myScanner.setLine(stringLine);
// 					Token t = myScanner.scanToken();
// 					tokenCount++;
// 					currValue = t.getValue();
// 					cout << t.toString() << endl;
// 					foundString = true;
// 					size_t i = inputLine.find(currValue);
// 					if (i != string::npos) {
// 						inputLine.erase(i, currValue.length());
// 						//cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
// 						for (unsigned int i = 0; i < inputLine.size(); i++) {
// 							if (isspace(inputLine.at(i))) inputLine = inputLine.substr(1); 
// 							//cout << i << " ";
// 						}
// 					}
// 					if (!inputLine.empty()) CommentAndStringCheck(inputLine, input,  line, tokenCount);
// 					break;
// 				}
// 				else if (!input.eof() || !inputLine.empty()) {
// 					//cout << "!eof" << endl;
// 					inputString = inputString + inputLine + "\n";
// 					inputLine.clear();
// 					getline(input, inputLine);
// 					line++;
// 					//cout << "\n" << inputLine;
// 				}
// 				else {
// 					//cout << "FALSESTRING" << endl;
// 					inputString = inputString + "FALSE_STRING";
// 					//cout << inputString;
// 					Scanner myScanner(inputString, stringLine);
// 					myScanner.setLine(stringLine);
// 					Token t = myScanner.scanToken();
// 					tokenCount++;
// 					currValue = t.getValue();
// 					cout << t.toString() << endl;
// 					foundString = true;
// 					size_t i = inputLine.find("\'"+currValue);
// 					if (i != string::npos) {
// 						inputLine.erase(i, currValue.length());
// 						//cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
// 						for (unsigned int i = 0; i < inputLine.size(); i++) {
// 							if (isspace(inputLine.at(i))) inputLine = inputLine.substr(1); 
// 							//cout << i << " ";
// 						}
// 					}
// 					if (!inputLine.empty()) CommentAndStringCheck(inputLine, input,  line, tokenCount);
// 					break;
// 				}
// 			}
// 			found = inputLine.find('\'');
// 			if (found != string::npos) {
// 				inputString = inputString + inputLine.substr(0,found+1);
// 				inputLine = inputLine.substr(found+1);
// 				//cout << "\n" << inputLine;
// 				//inputLine.clear();
// 				Scanner myScanner(inputString, line);
// 				myScanner.setLine(stringLine);
// 				Token t = myScanner.scanToken();
// 				tokenCount++;
// 				currValue = t.getValue();
// 				cout << t.toString() << endl;
// 				foundString = true;
// 				size_t i = inputLine.find('\''+currValue);
// 				if (i != string::npos) {
// 					inputLine.erase(i, currValue.length());
// 					//cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
// 					for (unsigned int i = 0; i < inputLine.size(); i++) {
// 						if (isspace(inputLine.at(i))) inputLine = inputLine.substr(1); 
// 						//cout << i << " ";
// 					}
// 				}
// 				if (!inputLine.empty()) CommentAndStringCheck(inputLine, input,  line, tokenCount);
// 				break;
// 			}	
// 			else if (!input.eof() || !inputLine.empty()) {
// 				//cout << "!eof " << inputString << endl;
// 				inputString = inputString + inputLine + "\n";
// 				//inputLine.clear();
// 				getline(input, inputLine);
// 				line++;
// 			}
// 			else {
// 				inputString = inputString + "FALSE_STRING";
// 				//cout << inputString;
// 				Scanner myScanner(inputString, line);
// 				myScanner.setLine(stringLine);
// 				Token t = myScanner.scanToken();
// 				tokenCount++;
// 				currValue = t.getValue();
// 				cout << t.toString() << endl;
// 				foundString = true;
// 				size_t i = inputLine.find("\'"+currValue);
// 				if (i != string::npos) {
// 					inputLine.erase(i, currValue.length());
// 					//cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
// 				}
// 				if (!inputLine.empty()) CommentAndStringCheck(inputLine, input,  line, tokenCount);
// 				break;
// 				}
// 		// 	else if (!input.eof() || !inputLine.empty()) {
// 		// 		//cout << "!eof" << endl;
// 		// 		inputString = inputString + inputLine;
// 		// 		inputLine.clear();
// 		// 		getline(input, inputLine);
// 		// 		line++;
// 		// 		//cout << "\nnewINput " << inputLine << endl;
// 		// 	}
// 		// 	else {
// 		// 		inputString = inputString + "FALSE_STRING";
// 		// 			//cout << inputString;
// 		// 			Scanner myScanner(inputString, line);
// 		// 			myScanner.setLine(line);
// 		// 			Token t = myScanner.scanToken();
// 		// 			tokenCount++;
// 		// 			currValue = t.getValue();
// 		// 			cout << t.toString() << endl;
// 		// 			foundString = true;
// 		// 			size_t i = inputLine.find("\'"+currValue);
// 		// 			if (i != string::npos) {
// 		// 				inputLine.erase(i, currValue.length());
// 		// 				//cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
// 		// 			}
// 		// 			if (!inputLine.empty()) CommentAndStringCheck(inputLine, input,  line, tokenCount);
// 		// 			break;
// 		// 	}
// 		}
// 	}
// 	else if (inputLine.at(0) == '#' &&   inputLine.size() > 1) {
// 		//cout << "in comment section";
// 		size_t found = inputLine.find("#|");
// 		if (found != string::npos) {
// 			//cout <<"FOUND #| " << endl;
// 			string finalInput = inputLine.substr(0,found+2);
// 			inputLine = inputLine.substr(found+2);
// 			while (!foundComment) {
// 				string newInput;
// 				getline(input, newInput);
// 				inputLine = inputLine + newInput;
// 				found = inputLine.find("#|");
// 				if (found != string::npos) {
// 					foundComment = true;
// 					finalInput = finalInput + inputLine;
// 					inputLine = inputLine.substr(found+2);
// 					Scanner myScanner(finalInput, line);
// 					myScanner.setLine(line);
// 					Token t = myScanner.scanToken();
// 					tokenCount++;
// 					currValue = t.getValue();
// 					cout << t.toString() << endl;
// 					size_t i = inputLine.find("#|"+currValue);
// 					if (i != string::npos) {
// 						inputLine.erase(i, currValue.length());
// 						//cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
// 					}
// 					if (!inputLine.empty()) CommentAndStringCheck(inputLine, input,  line, tokenCount);
// 				}
// 				else if (input.eof()) {
// 					//cout << "found eof" << endl;
// 					finalInput = finalInput + inputLine + "ERROR_EOF";
// 					Scanner myScanner(finalInput, line);
// 					myScanner.setLine(line);
// 					Token t = myScanner.scanToken();
// 					tokenCount++;
// 					currValue = t.getValue();
// 					cout << t.toString() << endl;
// 					foundComment = true;
// 					inputLine.clear();
// 					size_t i = inputLine.find("#|"+currValue);
// 					if (i != string::npos) {
// 						inputLine.erase(i, currValue.length());
// 						//cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
// 					}
// 					if (!inputLine.empty()) CommentAndStringCheck(inputLine, input, line, tokenCount);
// 				}
// 			}
// 		}
// 		else {
// 			foundComment = true;
// 			//cout << "FOUNDCOMMENT " << endl;
// 			Scanner myScanner(inputLine, line);
// 			myScanner.setLine(line);
// 			Token t = myScanner.scanToken();
// 			tokenCount++;
// 			currValue = t.getValue();
// 			cout << t.toString() << endl;

// 			size_t i = inputLine.find(currValue);
// 			if (i != string::npos) {
// 				inputLine.erase(i, currValue.length());
// 				//cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
// 			}
// 			if (!inputLine.empty()) CommentAndStringCheck(inputLine, input, line, tokenCount);
// 		}
// 	}

   vector<Token> tokens = {
    Token(COMMA,",",2),
    Token(ID,"Ted",2),
    Token(COMMA,",",2),
    Token(ID,"Zed",2),
    Token(RIGHT_PAREN,")",2),
  };

  Parser p = Parser(tokens);
  p.idList();
}