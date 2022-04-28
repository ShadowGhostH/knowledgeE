#pragma once
#include "uncertainCon.hpp"

class UncertainSearch {
protected:
    vector<UnCondition> evidenceList;
    vector<UnCondition> resultList;

    vector<Centence> centenceList;

    UnCondition& getCondition(string word);

    void getInitCondition();

    bool judgeCentence(Centence& cen);
    string printCentence(Centence& cen);

    void lsSearch(Int id);
    void lnSearch(Int id);

public:
    void solve();

    UncertainSearch();
    UncertainSearch(string filePath);
};
