#include "Token.h"
#include "Scanner.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main () {
	ifstream input ("input.txt");
	ofstream output ("output.txt");
	string inputLine;
	string endOfFile = "EOF";
	string currValue;
	int line = 1;

	while ( !input.eof() || input.eof() ) {
		cout << "\nSize:" << inputLine.size() << inputLine;
		if (input.eof()) {
			line++;
			Scanner myScanner(endOfFile, line);
			myScanner.setLine(line);
			Token t = myScanner.scanToken();
			output << t.toString() << endl;
			break;
		}
		if(inputLine.empty()) {
			cout << "Getline1 ";
			inputLine = "";
			getline(input, inputLine);
			line++;
		}
		else {
			std::string::size_type i = inputLine.find(currValue);
			if (i != std::string::npos) {
   				inputLine.erase(i, currValue.length());
				cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
				for (int i = 0; i < inputLine.size(); i++) {
					if (isspace(inputLine.at(i))) inputLine = inputLine.substr(1); 
					cout << i << " ";
				}
			}
		}
		if(inputLine.size() == 0 || inputLine == "") {
			cout << "Getline2 ";
			inputLine = "";
			getline(input, inputLine);
			cout << "New line = " << inputLine;
			line++;
		}
		while (!inputLine.empty()) {
			//Get rid of whitspace
			while(!inputLine.empty() && isspace(inputLine.at(0))) {
				inputLine = inputLine.substr(1);
			}
			//Check for comments and strings
			cout << "Inputline = " << inputLine << " size = " << inputLine.size() << endl;
			if (inputLine.at(0) == '\'' &&   inputLine.size() > 1) {
				size_t found = inputLine.find('\'\'');
				cout << "Found \'";
				if(found != string::npos) {
					stringstream ss;
					found;
					ss << inputLine.substr(0,found);
					inputLine = inputLine.substr(0,found);
					cout << "NEW INPUTLINE - " << inputLine << endl;
					found = inputLine.find('\'');
					if (found != string::npos) {
						ss << inputLine.substr(0,found);
						inputLine = inputLine.substr(0,found);
					}
					else if (!input.eof()) {
						cout << "!eof" << endl;
						ss << inputLine;
						getline(input, inputLine);
					}
					else {
						cout << "FALSESTRING" << endl;
						ss << "FALSE_STRING";
						cout << ss.str();
						Scanner myScanner(ss.str(), line);
						myScanner.setLine(line);
						Token t = myScanner.scanToken();
						currValue = t.getValue();
						output << t.toString() << endl;
					}
				}
			}
			/* 
				Initialize scanner and tokens
			*/
			Scanner myScanner(inputLine, line);
			myScanner.setLine(line);
			Token t = myScanner.scanToken();
			currValue = t.getValue();
			output << t.toString() << endl;
			std::string::size_type i = inputLine.find(currValue);
			if (i != std::string::npos) {
   				inputLine.erase(i, currValue.length());
				cout << "\nErased something " << inputLine << " " << inputLine.size() << endl;
				for (int i = 0; i < inputLine.size(); i++) {
					if (isspace(inputLine.at(i))) inputLine = inputLine.substr(1); 
					cout << i << " ";
				}
			}
		}
	}
	cout << "\nExiting while loop.";
	
	/* cout << "\n\\Beginning SCANNING\\" << endl;
	Scanner s = Scanner(" ,,");
	Token t= s.scanToken();
	cout << t.toString() << endl; */
}
