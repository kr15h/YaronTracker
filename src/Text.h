#pragma once

#include "ofMain.h"
#include "Library.h"

namespace ytr{

class Text{
public:
	static shared_ptr<Text> create(string text);
	string getNextWord();

private:
	Text(string text = "Default text");
	vector<string> _words;
	unsigned int _currWord;
};

} // namespace ytr
