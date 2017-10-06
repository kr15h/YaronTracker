#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "CameraFactory.h"
#include "ofxCv.h"

namespace ytr{

class CameraAll : public Camera{
public:
	void update();
	void draw();
	ofPixels & getPixels();
	cv::Mat & getFrame();
	bool isFrameNew();
	int getWidth();
	int getHeight();
	
private:
	CameraAll();
	
	ofVideoGrabber _videoGrabber;
	
	struct{
		int width;
		int height;
	} _dimensions;
	
	cv::Mat _frame;
	
	friend class CameraFactory;
};

} // namespace ytr
