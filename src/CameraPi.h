#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "CameraFactory.h"
#include "ofxCv.h"
#include "ofxCvPiCam.h"

namespace ytr{

class CameraPi : public Camera{
public:
	void update();
	void draw();
	cv::Mat & getFrame();
	bool isFrameNew();
	int getWidth();
	int getHeight();
	
private:
	CameraPi();
	
	ofxCvPiCam _cam;
	
	struct{
		int width;
		int height;
	} _dimensions;
	
	friend class CameraFactory;
};

} // namespace ytr
