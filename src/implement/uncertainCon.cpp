#include "uncertainCon.hpp"

UnCondition::UnCondition() {
    type = CONDITION_TYPE::FACT;
    state = CONDITION_STATE::UNKNOWN;
    description = "";
    index = -1;
}

UnCondition::UnCondition(string word, string description) {
    string flag = word.substr(0,1);
    Int index = std::stoi(word.substr(1));

    if(flag == FACT_WORD) type = CONDITION_TYPE::FACT;
    else if(flag == MEAN_WORD) type = CONDITION_TYPE::MEAN;
    else if(flag == EVIDENCE_WORD) type = CONDITION_TYPE::EVIDENCE;
    else if(flag == RESULT_WORD) type = CONDITION_TYPE::RESULT;

    state = CONDITION_STATE::UNKNOWN;

    this->description = description;
    this->index = index;
    this->word  = word;
}