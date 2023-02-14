#include "Predicate.h"
#include <vector>
class Rule {
	private:
		Predicate headPredicate;
		vector<Predicate> premises;
	public:
		string toString() {
			return headPredicate.toString();
		}
};