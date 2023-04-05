#include "Node.h"
#include "Graph.h"
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
//#include "DatalogProgram.h"
#include "Interpreter.h"
#include "Relation.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int main() {

  // predicate names for fake rules
  // first is name for head predicate
  // second is names for body predicates
  pair<string,vector<string>> ruleNames[] = {
    { "A", { "B" } },
    { "B", { "B", "A" } },
  };

  vector<rule> rules;

  for (auto& rulePair : ruleNames) {
    string headName = rulePair.first;
    rule Rule = rule(predicate(headName));
    vector<string> bodyNames = rulePair.second;
    for (auto& bodyName : bodyNames)
      Rule.addBodyPredicate(predicate(bodyName));
    rules.push_back(Rule);
  }

  Graph graph = Interpreter::makeGraph(rules);
  cout << graph.toString();

}