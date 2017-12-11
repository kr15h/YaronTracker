#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "Text.h"
#include "Settings.h"

namespace ytr {

class Text;

class Library{
public:
	static shared_ptr<Library> instance();
	
	struct {
		ofImage arrow;
	} images;
	
	ofxTrueTypeFontUC font;
	shared_ptr<Text> text;

private:
	static shared_ptr<Library> _instance;
	Library();
};

} // namespace ytr
