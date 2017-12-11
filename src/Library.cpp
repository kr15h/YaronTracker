#include "Library.h"

namespace ytr {

shared_ptr<Library> Library::_instance = 0;

shared_ptr<Library> Library::instance(){
	if(_instance == 0){
		_instance = shared_ptr<Library>(new Library);
	}
	return _instance;
}

Library::Library(){
	images.arrow.load("arrow.png");
	
	// string filename, int fontsize, bool bAntiAliased,
	// bool makeContours, float simplifyAmt, int dpi
	string fontFile = Settings::instance()->xml.getValue("text/font/file");
	int fontSize = ofToInt(Settings::instance()->xml.getValue("text/font/size"));
	font.loadFont(fontFile, fontSize, true, true, 1, 72);

	// Load text file
	string textFile = Settings::instance()->xml.getValue("text/file");
	ofFile file;
	file.open(textFile);
	ofBuffer buffer = file.readToBuffer();
	text = Text::create(buffer.getText());
}

} // namespace ytr
