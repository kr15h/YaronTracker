#pragma once

#include "ofMain.h"

#include "Mode.h"
#include "ModeDefault.h"
#include "ModeCalibrate.h"

#include "Camera.h"
#include "Tracker.h"
#include "Projection.h"

namespace ytr{

class Application{
public:
	static shared_ptr<Application> instance();
	
	void update();
	void draw();
	
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	
	void setMode(Mode::Name $name);
	
	shared_ptr<Camera> camera;
	shared_ptr<Tracker> tracker;
	shared_ptr<Projection> projection;

private:
	static shared_ptr<Application> _instance;
	Application();
	
	shared_ptr<Mode> _mode;

};

} // namespace ytr
