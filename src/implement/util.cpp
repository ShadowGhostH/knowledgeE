#include "util.hpp"

const Int inf = 0x3f3f3f3f;

const string &COMMENT_WORD = "*";
const string &FACT_WORD = "F";
const string &MEAN_WORD = "M";
const string &EVIDENCE_WORD = "E";
const string &RESULT_WORD = "H";
const string &CONDITION_IF = "IF";
const string &CONDITION_THEN = "THEN";

TimePoint startTime;		// global variable

const bool DEBUG = true;

const string &REQUIRED_OPTION_GROUP = "Required";
const string &OPTIONAL_OPTION_GROUP = "Optional";

const string &HELP_OPTION = "h, hi";
const string &INPUT_FILE_OPTION = "i";
const string &K_OPTION = "k";
const string &PRE_LOWER_BOUND_OPTION = "lb";
const string &TIME_LIMIT_OPTION = "tl";
const string &MEMORY_LIMIT_OPTION = "ml";

const Int DEFAULT_PRE_LOWER_BOUND = 0;
const Float DEFAULT_TIME_LIMIT = -1;

const Ull MEM_GB = 1073741824;
const Int DEFAULT_MEMORY_LIMIT = 8;				// 3.20 8G for searching on Server

Ull util::encode_pairID(Ull u, Ull v) {
    Ull pairID;
    Ull n = std::min(u, v);
    Ull m = std::max(u, v);
    pairID = ((n + m + 1) * (n + m) >> 1) + m;
    return pairID;
}

/* functions: print  ********************************************************/
void util::printComment(const string &message, Int preceedingNewLines, Int followingNewLines, bool commented) {
	for (Int i = 0; i < preceedingNewLines; i++) cout << endl;
	cout << (commented ? COMMENT_WORD + " " : "") << message;
	for (Int i = 0; i < followingNewLines; i++) cout << endl;
}

void util::printBoldLine(bool commented) {
	printComment("******************************************************************", 0, 1, commented);
}

void util::printThickLine(bool commented) {
	printComment("==================================================================", 0, 1, commented);
}

void util::printThinLine() {
	printComment("------------------------------------------------------------------");
}

/* functions: timing **********************************************************/

TimePoint util::getTimePoint() {
    return std::chrono::steady_clock::now();
}

Float util::getSeconds(TimePoint startTime) {
    TimePoint endTime = getTimePoint();
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / 1000.0;
}

void util::printDuration(TimePoint startTime) {
    printThickLine();
    printRow("seconds", getSeconds(startTime));
    printThickLine();
}


/* functions: error handling **************************************************/

void util::showWarning(const string &message, bool commented) {
	printBoldLine(commented);
	printComment("MY_WARNING: " + message, 0, 1, commented);
	printBoldLine(commented);
}

void util::showError(const string &message, bool commented) {
	throw MyError(message, commented);
}

MyError::MyError(const string &message, bool commented) {
	util::printBoldLine(commented);
	util::printComment("MY_ERROR: " + message, 0, 1, commented);
	util::printBoldLine(commented);
}