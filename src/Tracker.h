#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "Settings.h"
#include "ofxCv.h"

#ifdef TARGET_RASPBERRY_PI
#include "ofxCvPiCam.h"
#endif

namespace ytr {

class Tracker{
public:
	static shared_ptr<Tracker> create();
	
	void update();
	void draw();
	
	// We need 4 points to create a quad to cut an
	// area of interest from each incoming camera frame.
	void setTrackArea(vector<ofPoint> & $corners);
	
	// The position returned is the location of the tracked
	// object. This position is in pixels. If the image is 800px wide,
	// the position is going to be between 0 and 800. Use getWidth()
	// and getHeight() to normalize it.
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
	
	ofImage _warped;
	
	ofxCv::ContourFinder _contourFinder;
	
	ofVec2f _position;
	
	// These define which area should be taken from the incoming
	// camera image (_areaSrcPoints) and to what shape it should be
	// warped (_areaDstPoints).
	vector<cv::Point2f> _areaSrcPoints;
	vector<cv::Point2f> _areaDstPoints;
};

} // namespace ytr
