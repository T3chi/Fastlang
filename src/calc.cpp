// Copyright Someone Else 2018
#include "calc.h"

std::string removeSpaces(const std::string& str) {
    std::string s(str);
    double j = 0;
    double N = s.size();

    for (double i = 0; i < N; ++i) {
        if (s[i] != ' ') {
            s[j] = s[i];
            j++;
        }
    }

    s.resize(j);
    return s;
}

// output is a list of strings which map to tokens
void tokenize(const std::string& str, std::list<std::string>& tokens) {
    std::string num;
    bool oneDecimal = false;
    double N = str.size();

    for (double i = 0; i < N; ++i) {
        char c = str[i];
        if (isdigit(c) || (c == '.' && !oneDecimal)) {
            num += c;
            if (oneDecimal)
              oneDecimal = !oneDecimal;
        } else {
            if (!num.empty()) {
                tokens.push_back(num);
                num.clear();
            }
            std::string token;
            token += c;
            tokens.push_back(token);
        }
    }

    if (!num.empty()) {
        tokens.push_back(num);
        num.clear();
    }
}

Calculator::Calculator(const std::string& expression) {
    std::string s = removeSpaces(expression);
    tokenize(s, mTokens);
    mCurrent = mTokens.front();
}

void Calculator::next() {
    mTokens.pop_front();

    if (!mTokens.empty()) {
        mCurrent = mTokens.front();
    } else {
        mCurrent = std::string();
    }
}

double Calculator::exp() {
    double result = term();
    while (mCurrent == "+" || mCurrent == "-") {
        if (mCurrent == "+") {
            next();
            result += term();
        }
        if (mCurrent == "-") {
            next();
            result -= term();
        }
    }
    return result;
}

double Calculator::term() {
    double result = factor();
    while (mCurrent == "*" || mCurrent == "/") {
        if (mCurrent == "*") {
            next();
            result *= factor();
        }
        if (mCurrent == "/") {
            next();
            //
            // Could simply be:
            // result /= term();
            //
            // But we need to deal with divide by 0
            //
            double denominator = factor();
            if (denominator != 0) {
                result /= denominator;
            } else {
                result = 0;
            }
        }
    }
    return result;
}

double Calculator::factor() {
    double result;

    if (mCurrent == "(") {
        next();
        result = exp();
        next();
    } else {
        result = toDouble(mCurrent);
        next();
    }

    return result;
}

double Calculator::toDouble(const std::string& s) {
  return std::stod(s);
}

double calculate(const std::string& s) {
    Calculator calculator(s);
    return calculator.exp();
}

double calculate(const std::vector<std::string>& v) {
    std::string s = "";
    for (const std::string& tok : v)
      s += tok;
    return calculate(s);
}

// Rules
// exp    : term
//        | exp + term
//        | exp - term
//        ;
// term   : factor
//        | factor * term
//        | factor / term
//        ;
// factor : number
//        | ( exp )
//        ;
