#include "uncertainSearch.hpp"

UnCondition& UncertainSearch::getCondition(string word) {
    string flag = word.substr(0, 1);
    Int index = std::stoi(word.substr(1));

    if (flag == EVIDENCE_WORD)
        return evidenceList.at(index);
    else
        return resultList.at(index);
}

void UncertainSearch::getInitCondition() {
    cout << "Author: xuzh" << endl;
    util::printThickLine();
    cout << "已读取相关规则，下面对证据进行询问" << endl;
    for(Int i = 1; i < evidenceList.size(); i++) {
        cout << "证据 " << evidenceList[i].word << ": " << evidenceList[i].description << " 是真实的吗 (y/n) ";
        string tmp;
        std::cin >> tmp;
        if(tmp == "y") evidenceList[i].state = CONDITION_STATE::TRUE;
        else if(tmp == "n") evidenceList[i].state = CONDITION_STATE::FALSE;
    }

    for(Int i = 1; i < resultList.size(); i++) {
        cout << "事实 " << resultList[i].word << ": " << resultList[i].description << " 是真实的先验概率是：";
        std::cin >> resultList[i].p;
        resultList[i].o = resultList[i].p / (1 - resultList[i].p);
    }
    util::printThickLine();
}

bool UncertainSearch::judgeCentence(Centence& cen) {
    for(auto clause : cen.conditions) {
        bool flag = false;
        for(auto word : clause) {
            UnCondition& con = getCondition(word);
            if(con.state == CONDITION_STATE::TRUE) {
                flag = true;
                break;
            }
        }
        if(!flag) return false;
    }  
    return true;
}

string UncertainSearch::printCentence(Centence& cen) {
    string ret = "";
    bool andFlag = false;
    for(auto clause : cen.conditions) {
        if(andFlag) ret += " AND ";
        for(Int i = 0; i < clause.size(); i++) {
            if(i) ret += " OR ";
            ret += clause[i];
        }
    }  
    return ret;
}

void UncertainSearch::lsSearch(Int id) {
    string eviStr = "E" + to_string(id + 1) + "'";
    string resStr = centenceList[id].result;
    string oStr = "O(" + resStr + "|" + eviStr + ") = ";
    string pStr = "P(" + resStr + "|" + eviStr + ") = ";
    
    UnCondition res = getCondition(resStr);
    
    Float oValue = centenceList[id].LS * res.o;
    Float pValue = oValue / (1 + oValue);
    cout << "由于 " << printCentence(centenceList[id]) << " 为真，记此处对应证据为 " << eviStr 
         << " 可得：后验几率 " << oStr << oValue << " 后验概率 " << pStr << pValue << endl;     
}

void UncertainSearch::lnSearch(Int id) {
    string eviStr = "E" + to_string(id + 1) + "'";
    string resStr = centenceList[id].result;
    string oStr = "O(" + resStr + "|~" + eviStr + ") = ";
    string pStr = "P(" + resStr + "|~" + eviStr + ") = ";
    
    UnCondition res = getCondition(resStr);
    
    Float oValue = centenceList[id].LN * res.o;
    Float pValue = oValue / (1 + oValue); 
    cout << "由于 " << printCentence(centenceList[id]) << " 为假，记此处对应证据为 " << eviStr 
         << " 可得：后验几率 " << oStr << oValue << " 后验概率 " << pStr << pValue << endl;      
}

void UncertainSearch::solve() {
    getInitCondition();
    for(Int i = 0; i < centenceList.size(); i++) {
        if(judgeCentence(centenceList[i])) {
            lsSearch(i);
        } else {
            lnSearch(i);
        }
    }
}

UncertainSearch::UncertainSearch(string filePath) {
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
            vector<string> clause;
            for (Int i = 1; i < wordCount; i++) {
                if (words.at(i) == CONDITION_THEN) {
                    resultFlag = true;
                    continue;
                }
                if (!resultFlag) {
                    clause.push_back(words.at(i));
                    if(words.at(i + 1) == "OR") i++;
                    else if(words.at(i + 1) == "AND") { 
                        curCentence.conditions.push_back(clause);
                        clause.clear();
                        i++;
                    } else if(words.at(i + 1) == "THEN") {
                        curCentence.conditions.push_back(clause);
                        resultFlag = true;
                        i++;
                    }
                }
                else {
                    curCentence.result = words.at(i);
                    curCentence.LS = std::stod(words.at(i + 2));
                    curCentence.LN = std::stod(words.at(i + 4));
                    break;
                }
            }
        } else {
            string flag = startWord.substr(0, 1);
            Int index = std::stoi(startWord.substr(1));

            if (flag == EVIDENCE_WORD) {
                if (evidenceList.size() < index + 1) evidenceList.resize(index + 1);
                evidenceList[index] = UnCondition(startWord, words.at(1));
            } else if (flag == RESULT_WORD) {
                if (resultList.size() < index + 1) resultList.resize(index + 1);
                resultList[index] = UnCondition(startWord, words.at(1));
            }
        }
    }
}