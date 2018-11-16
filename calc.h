// Copyright Someone Else
#pragma once
#include <string>
#include <list>
#include <vector>

class Calculator {
 public:
explicit Calculator(const std::string& expression);
void next();
double exp();
double term();
double factor();
double toDouble(const std::string& s);
 private:
std::list<std::string> mTokens;
std::string mCurrent;
};

double calculate(const std::string& s);
double calculate(const std::vector<std::string>& v);
