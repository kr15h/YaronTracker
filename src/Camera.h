#pragma once

#include "ofMain.h"

namespace ytr{

class Camera{
public:
	static shared_ptr<Camera> instance();
	
	void update();
	void draw();
	ofTexture & getTexture();
	
private:
	Camera();
	static shared_ptr<Camera> _instance;
	
	ofVideoGrabber _videoGrabber;
	
	struct{
		int width;
		int height;
	} _dimensions;
};

} // namespace ytr
