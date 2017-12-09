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
	font.loadFont("DIN Alternate Bold.ttf", 64, true, true, 1, 72);

	// Load text file
	ofFile file;
	file.open("gesetz.txt");
	ofBuffer buffer = file.readToBuffer();
	text = Text::create(buffer.getText());
}

} // namespace ytr
