// Copyright Sohum Trivedi 2018
// https://github.com/T3chi/expert-succotash.git
#include <fstream>
#include "Tokenizer.h"
#include "Parser.h"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::ifstream;

string getFileInput(const string& filename) {
        std::ifstream t(filename);
        std::string str((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
        return str;
}

void printV(const vector<string>& v) {
  for (const string& s : v)
    cout << s << ", ";
  cout << endl;
}

int main(int argc, char* argv[]) {
        const bool testRepl = false;
        const bool condensing = true;
        if (argc > 2) {
          string program = getFileInput(argv[1]);
          bool debug = (string(argv[2]) == "-d") ? true:false;
          Tokenizer lexer(program);
          Parser(debug, lexer.getTokens());
        } else if (!testRepl) {
                bool debug = false;
                if (argc > 1)
                  debug = (string(argv[1]) == "-d") ? true : false;
                string program = getFileInput("input.txt");
                Tokenizer lexer(program);
                if (condensing)
                  Parser(condensing, debug, lexer.getTokens());
                else
                  Parser(debug, lexer.getTokens());
        } else {
                Parser();
        }
}
