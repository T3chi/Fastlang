#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <cstdlib>

using std::string;
using std::vector;
using std::cout;
using std::endl;

class Tokenizer {
 public:
	const vector<string> tokenize(const string& s); 	
 private:
 	const vector<string> keywords = {"var","while","for","loop","if","else"};
	const vector<string> ops = {"==","!=",">=","<=","=","!","<",">","(",")",
																												 "{","}","[","]",};
 	const bool isKeyword(const string& s) const { 
 		for(unsigned i = 0; i < keywords.size(); i++)
 			if(keywords.at(i) == s)
 				return true;
 		return false;
 	}
 	
 	const bool isOp(const string& s) const { 
 		for(unsigned i = 0; i < ops.size(); i++)
 			if(ops.at(i) == s)
 				return true;
 		return false;
 	}
};
