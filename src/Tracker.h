#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "ofxOpenCv.h"
#include "Settings.h"

namespace ytr {

class Tracker{
public:
	static shared_ptr<Tracker> create(shared_ptr<Camera> $camera);
	
	void update();
	void drawGrayImage();
	void drawContours();
	void draw();
	
	void setTrackArea(vector<ofPoint> & $corners);
	
	ofVec2f getPosition();
	int getWidth();
	int getHeight();

private:
	Tracker(shared_ptr<Camera> $camera);
	shared_ptr<Camera> _camera;
	
	bool _updateDimensions;
	
	int _width;
	int _height;
	
	ofxCvContourFinder _contourFinder;
	ofxCvColorImage _colorImg;
	ofxCvGrayscaleImage _grayImage;
	ofxCvGrayscaleImage _threshImage;
	
	ofVec2f _position;
	
	vector<ofPoint> _corners;
};

} // namespace ytr
