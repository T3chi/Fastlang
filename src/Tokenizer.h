// Copyright Sohum Trivedi 2018
#pragma once
// #include "headers.h"
// using namespace std;
#include "Tokenizer.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
// #include <vector>
// #include <string>
#include <cctype>

using std::vector;
using std::find_if;
using std::string;
using std::stringstream;
using std::cout;
using std::endl;
using std::find;

class Tokenizer;

class Tokenizer {
 private:
    string _program = "";

    vector<string> tokens;

    vector<string> copyStringToVector(const string& wholeString);

    vector<string> removeComments(const vector<string>& t);

    bool debug = false;

 public:
    static void error(const string& recieved, const string& expected);

    static inline bool isNum(const string& num);

    const vector<string>& getTokens() const {
      return tokens;
    }

    explicit Tokenizer(const string& program);
};
