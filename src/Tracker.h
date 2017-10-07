#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "ofxCv.h"

#ifdef TARGET_RASPBERRY_PI
#include "ofxCvPiCam.h"
#endif

#include "ofxHomographyHelper.h"

namespace ytr {

class Tracker{
public:
	static shared_ptr<Tracker> create();
	
	void update();
	void draw();
	
	// We need 4 points to create a quad to cut an
	// area of interest from each incoming camera frame.
	void setTrackArea(vector<ofPoint> & $corners);
	
	// The position is already mapped to the application window rect.
	ofVec2f getPosition();
	
	// These return the width and height of the tracking area. The
	// tracking area matches camera dimensions.
	int getWidth();
	int getHeight();
	
#ifdef TARGET_RASPBERRY_PI
	ofxCvPiCam cam;
#else
	ofVideoGrabber cam;
#endif

private:
	Tracker();
	
	int _width;
	int _height;
	
	ofxCv::ContourFinder _contourFinder;
	
	ofVec2f _position;
	
	// These define which area should be taken from the incoming
	// camera image (_areaSrcPoints) and to what shape it should be
	// warped (_areaDstPoints).
	vector<cv::Point2f> _areaSrcPoints;
	vector<cv::Point2f> _areaDstPoints;
};

} // namespace ytr
