// Copyright Sohum Trivedi 2018

#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <regex>
#include "calc.h"
#include "Function.h"
#include "Tokenizer.h"
#include "Condensor.h"

using std::map;
using std::vector;
using std::string;
using std::to_string;
using std::cout;
using std::cin;
using std::endl;
using std::regex_match;
using std::regex;
using std::exception;
using std::out_of_range;
class Parser;

class Parser {
 private:
map<string,  double> doubleMap;
map<string, Function> functionMap;

template <typename T1,  typename T2>
const void  d(const T1 in,  const T2 value) const;

template <typename T>
const void d(const T t);

void  error(const string& s,  const int pos) const;

void  error(const string& s) const;

const void  checkEquals(const string& one,  const string& two);

const inline void  syntaxAssert(const bool b) const;

const inline bool  isNum(const string& s);

const inline bool  isAlpha(const string& s);

const inline bool  isVar(const string& s);

const inline bool isFunction(const string& s);

static const bool  isString(const string& str);

static const string  toString(const string& s);

const inline void  setVar(const string& s,  const double val);

const string  getTokenValue(const string& s);

vector<string>  getCondition(const vector<string>&tokens,
                             const unsigned index);

const bool checkCondition(const vector<string>& tokens);

template <typename lambdaNext, typename lambdaCurrent>
void getVectorBody(vector<string>& v, const string& delim,lambdaNext next, lambdaCurrent current);

const void  initialAssign(const string& name,  const int value);

void  assign(const string& name,  const int value);

bool debug = true;

bool condensing = false;

friend class Condensor;

 public:
  explicit Parser(const vector<string>& tokens);
  explicit Parser(bool c, bool d, const vector<string>& tokens);
  explicit Parser(bool d, const vector<string>& tokens);

  Parser();

  void interpret(bool d, const std::vector<string>& v);

  void  interpret(const vector<string>& tokens);

  void repl();
};
