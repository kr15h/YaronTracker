#pragma once

#include "ofMain.h"
#include "Application.h"
#include "Settings.h"

using namespace ytr;

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
};
