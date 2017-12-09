#include "Text.h"

namespace ytr{

shared_ptr<Text> Text::create(string text){
	return shared_ptr<Text>(new Text(text));
}

Text::Text(string text){

	// Convert newlines to spaces
	for (int i = 0; i < text.length();i++) {
	   if (text[i] == '\n' || text[i] == '\r') {
		   text[i] = ' ';
	   }
	}
	
	

	// Split text into words
	_words = ofSplitString(text, " ");
	_currWord = 0;
}

string Text::getNextWord(){
	string word = _words[_currWord];
	
	_currWord++;
	if(_currWord >= _words.size()){
		_currWord = 0;
	}
	
	return word;
}

} // namespace ytr
