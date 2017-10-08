#pragma once

#include "ofMain.h"

namespace ytr {

class Settings{
public:
	static shared_ptr<Settings> instance();
	bool save();
	ofXml xml;
	
	bool debug;
	
private:
	static shared_ptr<Settings> _instance;
	Settings();

};

} // namespace ytr
