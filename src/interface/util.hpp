#pragma once

/*** inclusions ***/
#include <algorithm>
#include <chrono>
#include <deque>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <iterator>
#include <utility>
#include <map>
#include <random>
#include <vector>
#include <list>
#include <queue>
#include <unistd.h>
#include <cstring>
#include <regex>
#include <unordered_map>
#include <unordered_set>

/*** uses       ***/
using std::string;
using std::queue;
using std::vector;
using std::pair;
using std::list;
using std::cout;
using std::cerr;
using std::endl;
using std::to_string;


#define p_name(a) cout << #a << "\t";
#define DIF(flag) if(DEBUG && flag)

/*** types      ***/
using Ull = uint_fast64_t;
using Int = int_fast32_t;
using Float = double;

using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

template<typename T> using Set = std::unordered_set<T>;
template<typename K, typename V> using Map = std::unordered_map<K, V>;

extern const Int inf;

extern const string &COMMENT_WORD;
extern const string &FACT_WORD;
extern const string &MEAN_WORD;
extern const string &RESULT_WORD;
extern const string &CONDITION_IF;
extern const string &CONDITION_THEN;

extern TimePoint startTime;     // global variable

/***    DEBUG   ***/
extern const bool DEBUG;

/***    Constants   ***/
extern const string &REQUIRED_OPTION_GROUP;
extern const string &OPTIONAL_OPTION_GROUP;

extern const string &HELP_OPTION;
extern const string &INPUT_FILE_OPTION;
extern const string &K_OPTION;
extern const string &PRE_LOWER_BOUND_OPTION;
extern const string &TIME_LIMIT_OPTION;
extern const string &MEMORY_LIMIT_OPTION;

extern const Int DEFAULT_PRE_LOWER_BOUND;
extern const Float DEFAULT_TIME_LIMIT;

extern const Ull MEM_GB;
extern const Int DEFAULT_MEMORY_LIMIT;

enum class CONDITION_TYPE {FACT, MEAN, RESULT};
enum class CONDITION_STATE {TRUE, FALSE, UNKNOWN};

namespace util {
    Ull encode_pairID(Ull v1, Ull v2);

    /* functions: print  ********************************************************/
    void printComment(const string &message, Int preceedingNewLines = 0, Int followingNewLines = 1, bool commented = true);
    
    void printBoldLine(bool commented);
    void printThickLine(bool commented = true);
    void printThinLine();
    
    /* functions: timing ********************************************************/

    TimePoint getTimePoint();
    Float getSeconds(TimePoint startTime);
    void printDuration(TimePoint startTime);

    /* functions: error handling ************************************************/

    void showWarning(const string &message, bool commented = true);
    void showError(const string &message, bool commented = true);

    /* functions: templates implemented in headers to avoid linker errors *******/
    template<typename T> void printRow(const string &name, const T &value) {
        cout << COMMENT_WORD << " " << std::left << std::setw(30) << name;
        cout << std::left << std::setw(15) << value << "\n";
    }

    template<typename T> void printContainer(const T &container) {
        cout << "printContainer:\n";
        for (const auto &member : container) {
            cout << "\t" << member << "\t";
        }
        cout << "\n";
    }

    template<typename T, typename P> bool isInContainer(const P &element, const T &container) {
        for (const auto &member : container) {
            if(member == element) return true;
        }
        return false;
    }
}

class MyError {
public:
  MyError(const string &message, bool commented);
};