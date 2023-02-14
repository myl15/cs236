#include <vector>
#include "Scanner.h"
#include "Token.h"
#include <string>
#include "Rule.h"
#include "Parser.h"
#include "DatalogProgram.h"

class Parameter {
	private:
		string name;
		bool isID;
	public:
		string toString() {
			return "FALSE";
		}
}