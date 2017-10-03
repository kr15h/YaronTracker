#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

namespace ytr {

class Tracker{
public:
	static shared_ptr<Tracker> create();
	
	void update();
	void draw();

private:
	Tracker();
	
};

} // namespace ytr
