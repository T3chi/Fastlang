// Copyright Sohum Trivedi 2018
#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <array>
#include <iostream>
#include "Parser.h"

using std::vector;
using std::string;
using std::ofstream;
using std::array;
using std::cout;
using std::endl;

class Condensor;

class Condensor {
 public:
  // takes a series of strings & compresses them for speed
  explicit Condensor(const vector<string>& statements);

 private:
  static bool cdebug;
  // takes a series of strings & outputs them to a .cpp file
  static void condense(const vector<string>& statements);

  // runs the cpp file
  static void run();
};

//bool Condensor::cdebug = true;
