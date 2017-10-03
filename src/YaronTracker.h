#pragma once

#include "ofMain.h"

namespace ytr{

class YaronTracker{
public:
	static shared_ptr<YaronTracker> instance();
	
	void setup();
	void update();
	void draw();

private:
	static shared_ptr<YaronTracker> _instance;
	YaronTracker();
	
	ofVideoGrabber _camera;
	ofTexture _cameraTexture;
	struct{
		int width;
		int height;
	}_cameraDimensions;

};

} // namespace ytr
