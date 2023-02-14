#include <vector>
#include <string>
#include "Parser.h"
#include "Token.h"
#include "Parameter.h"

class predicate {
    private:
        parameter head;
        vector<Parameter> parameters;
	public:
		string toString() {
			return name;
		}
		void isScheme(){
			match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);
		}
		void isFact() {

		}
		void isQuery() {

		}
}