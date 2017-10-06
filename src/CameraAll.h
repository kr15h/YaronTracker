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
	cv::Mat & getFrame(); // Should return grayscale image
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
	
	ofPixels _grayPixels;
	cv::Mat _frame;
	
	friend class CameraFactory;
};

} // namespace ytr
