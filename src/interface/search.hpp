#pragma once
#include "condition.hpp"

class ProductionSearch {
protected:
    // vector<Condition> conditionList;
    vector<Condition> factList;
    vector<Condition> meanList;
    vector<Condition> resultList;

    vector<Centence> centenceList;
    // Set<Int> GDB;          // global data base

    Condition& getCondition(string word);
    bool judge(Centence &cen);

    void forwardSearch();
    void backwardSearch();
    void bilateralSearch();

    void printCondition();
    void getInitCondition();
    void getMoreCondition();
    void getTrueResult(vector<string>& trueResult);
    void getWantedCondition(string word);
    void getNeedFactCnt(string word);
    string getNeedFact(string word);

    void printCentence(Centence &cen);

    void printResult(vector<string>& trueResult);
public:
    void solve();

    ProductionSearch();
    ProductionSearch(string filePath);
};
