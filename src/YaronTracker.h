#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "Tracker.h"

namespace ytr{

class YaronTracker{
public:
	static shared_ptr<YaronTracker> create();
	
	void update();
	void draw();

private:
	YaronTracker();
	
	shared_ptr<Camera> _camera;
	shared_ptr<Tracker> _tracker;

};

} // namespace ytr
