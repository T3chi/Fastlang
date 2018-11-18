// Copyright 2018 Sohum Trivedi
#include "uTok.h"

vector<string> Tokenizer::tokenize(const string& s) {

  // holds identified tokens
	vector<string> tokens;

	for(unsigned i = 0; i < s.length(); i++) {

		// holds current token
		string current = "";

		// skip whitespace
		while (isspace(s[i])) {
			i++;
			continue;
		}

		// eat up comments represented as # text #
		if (s[i]=="#") {
			i++;
			while(s[i] != "#")
				i++;
			continue;
		}

		// makes sure that doubles have only one decimal point
		bool hasDec = false;
		while (isdigit(s[i]) || (s[i] == '.')) {
			if(s[i]== '.' && !hasDec) {
				hasDec = true;
				current += s[i];
			}
			else {
				cout << "multiple decimal points in number, exiting..." << endl;
				exit(0);
			}
		}

		if (!current.empty()) {
			tokens.push_back(current);
			continue;
		}

		while (isalpha(s[i])) {
			current += s[i];
			if (isKeyword(current)) {
				// add keyword as a token and look for next token
				tokens.push_back(current);
				continue;
			}
		}

		if (!current.empty()) {
			tokens.push_back(current);
			continue;
		}

		//handles <= != < ! etc operators
		if (i < s.length()-2) {
			if(isOp(1,s[i])) {
				current = s[i++];
				if(isOp(current+s[i])) {
					tokens.push_back(current);
					continue;
				}
				tokens.push_back(current);
				continue;
			}
		}

		tokens.push_back(current);
	}
	return tokens;
}
