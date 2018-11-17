// Copyright Sohum Trivedi 2018
#include "Condensor.h"

bool Condensor::cdebug = true;

Condensor::Condensor(const vector<string>& statements) {
  condense(statements);
  run();
}

void Condensor::condense(const vector<string>& statements) {
        array<string, 3> headers;
        headers[0] = "#include <iostream>";
        headers[1] = "#include <string>";
        headers[2] = "#include Parser.h";
        headers[3] = "int main() {";
        ofstream ofs("condensed.cpp", ofstream::out);
        for (const string& s : headers) {
          ofs << s << endl;
          if (cdebug)
            cout << s<< endl;
        }
        for (const string& s : statements) {
          if (cdebug)
            cout << s<< endl;
          ofs << s << endl;
        }
        ofs << "}" << endl;
        ofs.close();
}

void Condensor::run() {
        system("g++ -std=c++11 -O3 condensed.cpp -o co");
        system("./co");
}
