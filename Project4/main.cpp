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

  Relation studentRelation("students", Scheme( {"ID", "Name", "Major"} ));

  vector<string> studentValues[] = {
    {"'42'", "'Ann'", "'CS'"},
    {"'64'", "'Ned'", "'EE'"},
  };

  for (auto& value : studentValues)
    studentRelation.addTuple(Tuple(value));

//   studentRelation.join(studentRelation);

Relation courseRelation("courses", Scheme( {"ID", "Course"} ));

  vector<string> courseValues[] = {
    {"'42'", "'CS 100'"},
    {"'32'", "'CS 232'"},
  };

  for (auto& value : courseValues)
    courseRelation.addTuple(Tuple(value));

  studentRelation.join(courseRelation);

}