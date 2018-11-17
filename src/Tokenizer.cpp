// Copyright Sohum Trivedi 2018
// #include "headers.h"
#include "Tokenizer.h"
/* #include <sstream>
 #include <algorithm>
 #include <vector>
 #include <string>
 #include <cctype> */

/* using std::vector;
   using std::find_if;
   using std::string;
   using std::stringstream;
   using std::cout;
   using std::endl; */

vector<string> Tokenizer::copyStringToVector(const string& wholeString) {
        vector<string> ret;
        stringstream inputStream(wholeString);
        string s;
        while (!inputStream.eof()) {
                inputStream >> s;
                ret.push_back(s);
        }
        ret.pop_back();
        if (debug) {
                cout << "Tokens Processed:" << endl;
                for (const string& s : ret)
                        cout << s <<", ";
                cout << endl;
                cout << "End Tokens" << endl;
        }
        return ret;
}

vector<string> Tokenizer::removeComments(const vector<string>& t) {
// needs completion
        vector<string> ret = t;
        auto start = find(ret.begin(), ret.end(), "/*");
        auto end = find(ret.begin(), ret.end(), "*/");
        ret.erase(start, end);
        return ret;
}

void Tokenizer::error(const string& recieved, const string& expected) {
        cout << "Recieved: "<< recieved << endl;
        cout << "Expected: " << expected << endl;
}

inline bool Tokenizer::isNum(const string& num) {
        return !num.empty() && std::find_if(num.begin(), num.end(),
                                            [](char c) {
                return !std::isdigit(c);
        }) == num.end();
}

Tokenizer::Tokenizer(const string& program) {
        _program = program;
        tokens = copyStringToVector(_program);
}
