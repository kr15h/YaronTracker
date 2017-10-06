#pragma once

#include "ofMain.h"
#include "ofxCv.h"

namespace ytr{

class Camera{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual cv::Mat & getFrame() = 0;
	virtual bool isFrameNew() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
};

} // namespace ytr
