#pragma once
#include "util.hpp"

class Condition {
protected:
    
public:
    CONDITION_TYPE type;
    CONDITION_STATE state;
    string description, word;
    Int index;
    Int needFactCnt;

    Condition();
    Condition(string word, string description);
};

class Centence {
public:
    vector<string> conditions;
    string result;
    bool state;
    Int needFact;
};
