#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "ofxOpenCv.h"

namespace ytr {

class Tracker{
public:
	static shared_ptr<Tracker> create(shared_ptr<Camera> $camera);
	
	void update();
	void drawGrayImage();
	void drawContours();
	void draw();
	
	ofVec2f getPosition();

private:
	Tracker(shared_ptr<Camera> $camera);
	shared_ptr<Camera> _camera;
	
	ofxCvContourFinder _contourFinder;
	ofxCvColorImage _colorImg;
	ofxCvGrayscaleImage _grayImage;
	ofxCvGrayscaleImage _threshImage;
	
	ofVec2f _position;
};

} // namespace ytr
