#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "Tracker.h"

namespace ytr{

class Application{
public:
	static shared_ptr<Application> create();
	
	void update();
	void draw();

private:
	Application();
	
	shared_ptr<Camera> _camera;
	shared_ptr<Tracker> _tracker;

};

} // namespace ytr
