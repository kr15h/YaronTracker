#pragma once

#include "ofMain.h"

namespace ytr{

class Camera{
public:
	static shared_ptr<Camera> create();
	
	void update();
	void draw();
	ofPixels & getPixels();
	bool isFrameNew();
	int getWidth();
	int getHeight();
	
private:
	Camera();
	
	ofVideoGrabber _videoGrabber;
	
	struct{
		int width;
		int height;
	} _dimensions;
};

} // namespace ytr
