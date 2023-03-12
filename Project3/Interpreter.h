#pragma once

#include <vector>
#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Predicate.h"

class Interpreter {
    private:
        DatalogProgram dp;
        Database db;
    public:
        Interpreter(DatalogProgram dp) : dp(dp) { 
            for (auto& scheme : dp.getSchemes()) {
                Relation(scheme.getName(), scheme.getParameterNames());
            }

            

        }


};