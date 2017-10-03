#pragma once

#include "ofMain.h"
#include "Camera.h"

namespace ytr{

class YaronTracker{
public:
	static shared_ptr<YaronTracker> instance();
	
	void update();
	void draw();

private:
	static shared_ptr<YaronTracker> _instance;
	YaronTracker();

};

} // namespace ytr
