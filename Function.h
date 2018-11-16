#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>  // for exit(0)

using std::string;
using std::vector;
using std::cout;
using std::endl;

class Function;

class Function {
 private:
vector<string> parameters;
vector<string> functionBody;
double ret = 0;

 public:
const vector<string> getParameters() const {
        return parameters;
}

const vector<string> getBody() const {
        return functionBody;
}

void setReturn(double d) {
        ret = d;
}

const double getReturn() const {
        return ret;
}

vector<string> substituteParameters(const vector<string>& tempParams) {
        // changes values of parameters in function body to called parameters
        vector<string> ret = functionBody;
        vector<string> oldParams = parameters;
        if (oldParams.size() != tempParams.size()) {
          cout << "size mismatch in substituteParameters in Function.h" << endl;
          exit(0);
        }
        for (string& tok : ret) {
          for (unsigned param = 0; param < oldParams.size(); param++) {
            if (tok == oldParams[param]) {
                tok = tempParams[param];
              }
          }
        }
      cout << "Function Body:" << endl;
      for (const string& s : ret) {
          cout << s << ", ";
      }
      cout << endl;
      cout<< "End function body" << endl;
      return ret;
}

Function() {
}

explicit Function(const vector<string>& p, const vector<string>& b) {
        parameters = p;
        functionBody = b;
}

};
