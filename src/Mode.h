#pragma once

#include "ofMain.h"

namespace ytr {

class Mode{
public:
	virtual void update(){};
	virtual void draw(){};
	virtual void keyPressed(int key){};
	virtual void mousePressed(int x, int y, int button){};
	
	enum Name {
		DEFAULT,
		CALIBRATE
	};
};

} // namespace ytr
