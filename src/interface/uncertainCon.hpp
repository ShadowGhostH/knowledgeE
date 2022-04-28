#pragma once
#include "util.hpp"

class UnCondition {
protected:
    
public:
    CONDITION_TYPE type;
    CONDITION_STATE state;
    string description, word;
    Int index;
    Float p, o;
    
    UnCondition();
    UnCondition(string word, string description);
};

class Centence {
public:
    vector<vector<string> > conditions;
    Float LS, LN;
    string result;
};
