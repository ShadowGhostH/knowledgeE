#include "search.hpp"

Condition& ProductionSearch::getCondition(string word) {
    string flag = word.substr(0, 1);
    Int index = std::stoi(word.substr(1));

    if (flag == FACT_WORD)
        return factList.at(index);
    else if (flag == MEAN_WORD)
        return meanList.at(index);
    else
        return resultList.at(index);
}

bool ProductionSearch::judge(Centence& cen) {
    if (cen.state)
        return true;
    Int needFact = 0;
    Condition& curResult = getCondition(cen.result);
    for (string con : cen.conditions) {
        Condition& curCondition = getCondition(con);
        if (curCondition.state == CONDITION_STATE::UNKNOWN) {
            return false;
        } else if (curCondition.state == CONDITION_STATE::FALSE) {
            return false;
        }
    }

    cen.state = true;
    return true;
}

void ProductionSearch::forwardSearch() {
    vector<string> trueResult;
    while (trueResult.size() == 0) {
        bool findDifferent = true;
        while (findDifferent) {
            findDifferent = false;
            for (Int i = 0; i < centenceList.size(); i++) {
                if (!centenceList[i].state && judge(centenceList[i])) {
                    Condition& res = getCondition(centenceList[i].result);
                    res.state = CONDITION_STATE::TRUE;
                    res.needFactCnt = 0;
                    findDifferent = true;
                }
            }
        }
        getTrueResult(trueResult);
        if (trueResult.size() == 0) {
            cout << "对不起, 根据已有信息，无法判断动物类型，请后续输入更多事实" << endl;
            getMoreCondition();
        }
    }

    printResult(trueResult);
}

void ProductionSearch::backwardSearch() {
}

void ProductionSearch::bilateralSearch() {
    vector<string> trueResult;
    while (trueResult.size() == 0) {
        bool findDifferent = true;
        while (findDifferent) {
            findDifferent = false;
            for (Int i = 0; i < centenceList.size(); i++) {
                if (!centenceList[i].state && judge(centenceList[i])) {
                    Condition& res = getCondition(centenceList[i].result);
                    
                    res.state = CONDITION_STATE::TRUE;
                    res.needFactCnt = 0;
                    
                    findDifferent = true;
                }
            }
        }
        getTrueResult(trueResult);
        if (trueResult.size())
            break;

        string needFact;
        Int minNeed = inf;

        for (Int i = 1; i < meanList.size(); i++)
            getNeedFactCnt(meanList[i].word);
        for (Int i = 1; i < resultList.size(); i++) {
            getNeedFactCnt(resultList[i].word);
            if (resultList[i].needFactCnt < minNeed) {
                minNeed = resultList[i].needFactCnt;
                needFact = getNeedFact(resultList[i].word);
            }
        }
        getWantedCondition(needFact);

        // for(auto cen : centenceList) {
        //     printCentence(cen);
        // }
    }

    printResult(trueResult);
}

void ProductionSearch::printCondition() {
    util::printThickLine();
    cout << "有相关的事实如下: " << endl;
    for (Int i = 1; i < factList.size(); i++) {
        cout << std::setw(5) << factList[i].word << ": " << factList[i].description << "\t";
        if (i % 4 == 0 && i != factList.size() - 1)
            cout << endl;
    }
    cout << endl;

    util::printThickLine();
}

void ProductionSearch::getInitCondition() {
    printCondition();
    cout << "请根据上述描述, 输入已知的事实(用空格隔开): ";
    string str;
    getline(std::cin, str);
    std::istringstream iss(str);
    while (iss >> str) {
        Condition& curCondition = getCondition(str);
        curCondition.state = CONDITION_STATE::TRUE;
        curCondition.needFactCnt = 0;
    }
}

void ProductionSearch::getMoreCondition() {
    cout << "请根据上述描述, 输入已知的事实(用空格隔开): ";
    string str;
    getline(std::cin, str);
    std::istringstream iss(str);
    while (iss >> str) {
        Condition& curCondition = getCondition(str);
        curCondition.state = CONDITION_STATE::TRUE;
        curCondition.needFactCnt = 0;
    }
}

void ProductionSearch::getTrueResult(vector<string>& trueResult) {
    for (Int i = 1; i < resultList.size(); i++) {
        if (resultList[i].state == CONDITION_STATE::TRUE) {
            trueResult.push_back(resultList[i].word);
        }
    }
}

string ProductionSearch::getNeedFact(string word) {
    Int minNeed = inf;
    string needFact = "";
    queue<string> meanQueue;
    for (Int i = 0; i < centenceList.size(); i++)
        if (centenceList[i].result == word) {
            for (string conStr : centenceList[i].conditions) {
                Condition& con = getCondition(conStr);
                if (con.state == CONDITION_STATE::UNKNOWN) {
                    if (con.type == CONDITION_TYPE::FACT)
                        needFact = con.word;
                    else if (con.type == CONDITION_TYPE::MEAN)
                        meanQueue.push(con.word);
                } else if (con.state == CONDITION_STATE::FALSE) {
                    needFact = "";
                    break;
                }
            }
            if (needFact != "")
                return needFact;
        }
    while (!meanQueue.empty()) {
        string conStr = meanQueue.front();
        meanQueue.pop();
        needFact = getNeedFact(conStr);
        if (needFact != "")
            return needFact;
    }
    return needFact;
}

void ProductionSearch::getNeedFactCnt(string word) {
    Int needFactCnt = inf;
    for (auto& cen : centenceList)
        if (cen.result == word) {
            Int curNeedFactCnt = 0;
            for (auto conStr : cen.conditions) {
                Condition& con = getCondition(conStr);
                if (con.state == CONDITION_STATE::FALSE)
                    curNeedFactCnt = inf;
                if (con.state == CONDITION_STATE::UNKNOWN) {
                    if (con.type == CONDITION_TYPE::FACT)
                        curNeedFactCnt += 1;
                    if (con.type == CONDITION_TYPE::MEAN)
                        curNeedFactCnt += con.needFactCnt;
                }
            }
            needFactCnt = std::min(needFactCnt, curNeedFactCnt);
        }
    Condition& con = getCondition(word);
    con.needFactCnt = needFactCnt;
}

void ProductionSearch::getWantedCondition(string word) {
    Condition& con = getCondition(word);
    cout << "请问，您所观察到的，符合 " << con.description << " 吗? (y/n)  ";
    string flag;
    std::cin >> flag;
    if (flag == "y") {
        con.state = CONDITION_STATE::TRUE;
        con.needFactCnt = 0;
    } else {
        con.state = CONDITION_STATE::FALSE;
    }
}

void ProductionSearch::printCentence(Centence& cen) {
    cout << "如果: ";
    for (auto conStr : cen.conditions) {
        Condition& con = getCondition(conStr);
        cout << con.description << " ";
    }
    cout << "\t 则: " << getCondition(cen.result).description << endl;

    /*
        for(auto conStr : cen.conditions) {
            Condition& con = getCondition(conStr);
            string state;
            switch(con.state) {
                case CONDITION_STATE::TRUE    : state = " :true\t needFact: "; break;
                case CONDITION_STATE::FALSE   : state = " :false\t needFact: "; break;
                case CONDITION_STATE::UNKNOWN : state = " :unknown \t needFact: "; break;
            }
            cout << con.description << state << con.needFactCnt << endl;
        }

        Condition& con = getCondition(cen.result);
        string state;
        switch(con.state) {
            case CONDITION_STATE::TRUE    : state = " :true\t needFact: "; break;
            case CONDITION_STATE::FALSE   : state = " :false\t needFact: "; break;
            case CONDITION_STATE::UNKNOWN : state = " :unknown \t needFact: "; break;
        }
        cout << con.description << state << con.needFactCnt << endl;
    */
}

void ProductionSearch::printResult(vector<string>& trueResult) {
    cout << "根据分析，您所描述的动物类型有可能是: ";
    for (Int i = 0; i < trueResult.size(); i++) {
        if (i)
            cout << "  或者 ";
        Condition& curCondition = getCondition(trueResult[i]);
        cout << curCondition.description;
    }
    cout << endl;
}

void ProductionSearch::solve() {
    getInitCondition();
    forwardSearch();
    // bilateralSearch();
}

ProductionSearch::ProductionSearch(string filePath) {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        util::showError("unable to open file '" + filePath + "'");
    }

    string line;
    while (std::getline(inputFile, line)) {
        std::istringstream inputStringStream(line);
        vector<string> words;
        std::copy(std::istream_iterator<string>(inputStringStream), std::istream_iterator<string>(), std::back_inserter(words));

        Int wordCount = words.size();
        if (wordCount < 1)
            continue;
        const string& startWord = words.at(0);

        if (startWord == COMMENT_WORD) {
            continue;
        } else if (startWord == CONDITION_IF) {
            bool resultFlag = false;
            centenceList.push_back(Centence());
            Centence& curCentence = *(centenceList.end() - 1);
            curCentence.state = false;
            for (Int i = 1; i < wordCount; i++) {
                if (words.at(i) == CONDITION_THEN) {
                    resultFlag = true;
                    continue;
                }
                if (!resultFlag)
                    curCentence.conditions.push_back(words.at(i));
                else
                    curCentence.result = words.at(i);
            }
        } else {
            string flag = startWord.substr(0, 1);
            Int index = std::stoi(startWord.substr(1));

            if (flag == FACT_WORD) {
                if (factList.size() < index + 1)
                    factList.resize(index + 1);
                factList[index] = Condition(startWord, words.at(1));
            } else if (flag == MEAN_WORD) {
                if (meanList.size() < index + 1)
                    meanList.resize(index + 1);
                meanList[index] = Condition(startWord, words.at(1));
            } else if (flag == RESULT_WORD) {
                if (resultList.size() < index + 1)
                    resultList.resize(index + 1);
                resultList[index] = Condition(startWord, words.at(1));
            }
        }
    }
}