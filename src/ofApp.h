#pragma once

#include "ofMain.h"
#include "Application.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	shared_ptr<ytr::Application> app;
};
