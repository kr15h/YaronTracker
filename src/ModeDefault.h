#pragma once

#include "ofMain.h"
#include "Mode.h"
#include "Application.h"
#include "Projection.h"

namespace ytr {

class Mode;

class ModeDefault : public Mode{
public:
	static shared_ptr<Mode> instance();

	void update();
	void draw();
	void keyPressed(int key);
	
private:
	static shared_ptr<Mode> _instance;
	ModeDefault();
};

} // namespace ytr
