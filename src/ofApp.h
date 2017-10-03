#pragma once

#include "ofMain.h"
#include "YaronTracker.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	shared_ptr<ytr::YaronTracker> _application;
};
