// Copyright Sohum Trivedi 2018
#include "Parser.h"

template <typename T1,  typename T2>
const void Parser::d(const T1 in,  const T2 value) const {
        if  ( debug )
                cout << "(debug 2) in: "<< in
                     << " with value: " << value
                     << endl;
}

template <typename T>
const void Parser::d(const T t) {
        if  (debug)
                cout << "(debug 1) in " << t << endl;
}

void Parser::error(const string& s,  const int pos) const {
        cout << "Error on token: \'" << s <<
                "\'" << " (token #" << pos << ")" << endl;
        exit(0);
}

void Parser::error(const string& s) const {
        cout << "Error: " << s << endl;
        exit(0);
}

const void Parser::checkEquals(const string& one,  const string& two)  {
        if  (one != two)
                error(one + " does not equal " + two);
}

const inline void Parser::syntaxAssert(const bool b) const {
        if  (b == false)
                error("syntaxAssert recieved false");
}

const inline bool Parser::isNum(const string& s) {
        d("isNum ("+s+")",  regex_match(s,  regex("^-?[0-9]+\\.?[0-9]*$")));
        return regex_match(s,  regex("^-?[0-9]+\\.?[0-9]*$"));
}

const inline bool Parser::isAlpha(const string& s) {
        d("isAlpha ("+s+")",  regex_match(s,  regex("^[a-zA-Z]+$")));
        return regex_match(s,  regex("^[a-zA-Z]+$"));
}

const inline bool Parser::isVar(const string& s) {
        d("isVar (double?) ("+s+")",  doubleMap.find(s) != doubleMap.end());
        d("isVar (function?) ("+s+")",  functionMap.find(s) != functionMap.end());
        return doubleMap.find(s) != doubleMap.end()
               || functionMap.find(s) != functionMap.end();
}

const inline bool Parser::isFunction(const string& s) {
        return functionMap.find(s) != functionMap.end();
}

const bool Parser::isString(const string& str) {
        if  ((str[0] == '"') && (str[str.size()-1] == '"'))
                return true;
        return false;
}

const string Parser::toString(const string& s) {
        string str = s;
        str.erase(0,  1);
        str.erase(str.size()-1,  1);
        return str;
}

const inline void Parser::setVar(const string& s,  const double val) {
        d("setVar (" + s + ", " + to_string(val) + ")");
        doubleMap[s] = val;
}

const string Parser::getTokenValue(const string& s) {
        // returns a string representing value of variable,  raw string,
        if (isVar(s)) {
                return to_string(doubleMap[s]);
        } else if (isString(s)) {
                return toString(s);
        } else if (isNum(s)) {
                return s;
        } else {
                d("getTokenValue", s);
                error(" Unexpected value passed to getTokenValue: " + s);
        }
        return "";
}
// ( i != 5 )
vector<string> Parser::getCondition(const vector<string>& tokens,
                                    const unsigned index) {
        vector<string> outputVector;
        unsigned i = index;
        checkEquals(tokens.at(++i),  "(");
        while  ( tokens.at(++i) != ")" ) {
                outputVector.push_back(tokens.at(i));
        }
        return outputVector;
}

const bool Parser::checkCondition(const vector<string>& toks) {
        d("check_condition");
        vector<string> tokens = toks;
        for (unsigned i = 0; i < tokens.size(); i++)
                if (isVar(tokens.at(i)))
                        tokens[i] = getTokenValue(tokens[i]);
        if (tokens.size() == 2) {
                bool v = tokens[1] == "true" ? true : false;
                checkEquals(tokens[0], "!");
                return !v;
        } else if (tokens.size() == 3) {
                string f = tokens.at(0);
                string op = tokens.at(1);
                string s = tokens.at(2);
                if (isNum(f) && isNum(s)) {
                        double first = stod(f), second = stod(s);
                        if (op == "==") {
                                return first == second;
                        } else if (op == "!=") {
                                return first != second;
                        } else if (op == "<=") {
                                return first <= second;
                        } else if (op == ">=") {
                                return first >= second;
                        } else if (op == "<") {
                                return first < second;
                        } else if (op == ">") {
                                return first > second;
                        } else if (op == "!=") {
                                return first != second;
                        } else {
                                error("unable to process numeric conditional");
                        }
                }
                else if (f == "true" || f == "false" && s == "true" || s == "false") {
                        bool first = f == "true" ? true : false;
                        bool second = s == "true" ? true : false;
                        if (op == "&&") {
                                return first && second;
                        } else if (op == "||") {
                                return first || second;
                        } else if (op == "!=") {
                                return first != second;
                        } else if (op == "==") {
                                return first == second;
                        } else {
                                error("unable to parse boolean expression");
                        }
                } else {
                        error("unable to evaluate conditional expression");
                }

        }
        // temp return val to get rid of warning
        return false;
}

template <typename lambdaNext, typename lambdaCurrent>
void getVectorBody(vector<string>& v, const string& delim, lambdaNext next,
                                                        lambdaCurrent current) {
        if (next() != delim) {
                unsigned delimCount = 0;
                do {
                        v.push_back(next());
                        if (current() == "{")
                                delimCount++;
                        // To Do: add argument for matching ending delim
                        else if (current() == delim)
                                delimCount--;
                } while (current() != delim || delimCount != 0);
        }
}

const void Parser::initialAssign(const string& name,  const int value) {
        if (doubleMap.find(name) != doubleMap.end())
                error(name + " has already been declared as a variable");
        else
                assign(name, value);
}

void Parser::assign(const string& name,  const int value) {
        doubleMap[name] = value;
}


Parser::Parser(bool c, bool d, const vector<string>& tokens) {
        condensing = c;
        Parser(d, tokens);
}

Parser::Parser(bool d, const vector<string>& tokens) {
        debug = d;
        interpret(tokens);
}

Parser::Parser(const vector<string>& tokens) {
        interpret(tokens);
}

Parser::Parser() {
        repl();
}

void Parser::interpret(bool d, const std::vector<string>& v) {
        debug = d;
        interpret(v);
}

void Parser::interpret(const vector<string>& tokens) {
        for (unsigned index = 0; index < tokens.size()-1; index++) {
                auto next = [&](){
                                    return tokens.at(++index);
                            };
                auto back = [&](){
                                    return tokens.at(--index);
                            };
                auto current = [&](){
                                       return tokens.at(index);
                               };
                if (current() == "}") {
                        d("closing brace return");
                        return;
                } else if (current() == "var") {
                        d("var_check");
                        string name = next(); syntaxAssert(isAlpha(name));
                        string eq = next(); syntaxAssert(eq == "=");
                        string num = next(); syntaxAssert(isNum(num));
                        syntaxAssert(next() ==";");
                        setVar(name, stod(num));
                } else if (current() == "~") {
                        /* ~ print ( a ) { println a ; } */
                        // to do : needs finishing
                        d("func_check");
                        string name = next(); syntaxAssert(isAlpha(name));
                        checkEquals(next(), "(");
                        vector<string> params;
                        if (next() != ")") {
                                unsigned parenCount = 1;
                                do {
                                        params.push_back(next());
                                        if (current() == "(")
                                                parenCount++;
                                        else if (current() == ")")
                                                parenCount--;
                                } while (current() != ")" || parenCount != 0);
                        }
                        checkEquals(current(), ")");
                        checkEquals(next(), "{");
                        vector<string> body;
                        unsigned braceCount = 1;
                        // To do: implement brace count checking for
                        // all other cases as well
                        do {
                                body.push_back(next());
                                if (current() == "{")
                                        braceCount++;
                                else if (current() == "}")
                                        braceCount--;
                        } while (current() != "}" || braceCount != 0);
                        checkEquals(current(), "}");
                        functionMap[name] = Function(params, body);
                        // need to store function in some sort of map
                }  else if (current() == "if ") {
                        d("if _check");
                        checkEquals(next(), "(");
                        vector<string> logic;
                        while (next() != ")")
                                logic.push_back(current());
                        checkEquals(current(), ")");
                        vector<string> body;
                        checkEquals(next(), "{");
                        while (next() != "}")
                                body.push_back(current());
                        checkEquals(current(), "}");
                        bool condition = checkCondition(logic);
                        if (condition) {
                                interpret(body);
                        } else if (!condition && next() == "else") {
                                vector<string> altBody(10);
                                checkEquals(next(), "{");
                                while (next() != "}")
                                        body.push_back(current());
                                checkEquals(current(), "}");
                                interpret(altBody);
                        } else {
                                back();
                        }
                } else if (current() == "print") {
                        d("print_check");
                        string toPrint = getTokenValue(next());
                        checkEquals(tokens.at(++index),  ";");
                        cout << toPrint;
                } else if (current() == "println") {
                        d("println_check");
                        if (next() == ";") {
                                cout << endl;
                                continue;
                        } else {
                                back();
                        }
                        string toPrint = getTokenValue(next());
                        checkEquals(next(),  ";");
                        cout << toPrint << endl;
                } else if (current() == "loop") {
                        d("loop_check");
                        string iter = next();
                        syntaxAssert(isNum(current()));
                        checkEquals(next(), "{");
                        vector<string> body;
                        while (current() != "}")
                                body.push_back(next());
                        // body.pop_back();
                        for (unsigned i = 0; i < stoi(iter); i++) {
                                try {
                                        interpret(body);
                                } catch(out_of_range& e) {
                                        cout << "Contents of vector for debug:"
                                             << endl;
                                        for (const string& s : body)
                                                cout << s << endl;
                                        error(
                                                string(
                                                        " exception caught executing" \
                                                        "'loop' instruction: ")
                                                + e.what());
                                }
                        }
                } else if (current() == "while") {
                        // To be implemented
                        d("while_check");
                        checkEquals(next(), "(");
                        vector<string> logic;
                        while (next() != ")")
                                logic.push_back(current());
                        checkEquals(current(), ")");
                        vector<string> body;
                        checkEquals(next(), "{");
                        while (next() != "}")
                                body.push_back(current());
                        checkEquals(current(), "}");
                        while (checkCondition(logic))
                                interpret(body);
                } else if (isAlpha(current())) {
                        string name = current();
                        if (!isVar(current())) {
                                error(" unknown identifier: " + current());
                        } else if (next() == "=") {
                                d("variable reassignment");
                                vector<string> math;
                                while (next() != ";") {
                                        if (isVar(current())) {
                                                math.push_back(getTokenValue(
                                                                       current()));
                                        } else {
                                                math.push_back(current());
                                        }
                                }
                                checkEquals(current(), ";");
                                d("calculate", calculate(math));
                                setVar(name, calculate(math));
                        } else if (current() == "(") {
                                // parse function
                                d("function execution");
                                syntaxAssert(isFunction(name));
                                Function called = functionMap[name];
                                vector<string> params;
                                while (next() != ")") {
                                        params.push_back(current());
                                }
                                if (params.size() != called.getParameters().size())
                                        error("function : " + name + " called with "
                                              + to_string(params.size())
                                              + " arguments when "
                                              + to_string(called.getParameters().size())
                                              + " arguments were expected");
                                checkEquals(current(), ")");
                                if (params.size() > 0) {
                                        for (unsigned i = 0; i < params.size(); i++)
                                                params[i] = getTokenValue(params[i]);
                                        interpret(called.substituteParameters(params));
                                } else {
                                        interpret(called.getBody());
                                }
                        }
                } else {
                        error(string(" Unrecognized Token '") + current()+"'");
                }
        }
}

void Parser::repl() {
        unsigned counter = 0;
        cout << "Type exit! to immediately exit" << endl;
        cout << "Type D! to enable/disable debug mode" << endl;
        string user_input = "";
        bool d = false;  // debug flag
        while (true) {
                counter++;
                cout << "$$$>>> ";
                getline(cin, user_input);
                if (user_input.find("exit!") != std::string::npos
                    || counter > 100) {
                        cout << "exiting..." << endl;
                        exit(0);
                } else if (user_input.find("D!") != std::string::npos) {
                        cout << "enabling debug..." << endl;
                        d = !d;
                }
                interpret(d, (Tokenizer(user_input)).getTokens());
        }
}
