#include "Tracker.h"

namespace ytr {

shared_ptr<Tracker> Tracker::create(){
	return shared_ptr<Tracker>(new Tracker);
}

Tracker::Tracker(){
	int w = ofToInt(Settings::instance()->xml.getValue("camera/width"));
	int h = ofToInt(Settings::instance()->xml.getValue("camera/height"));
	
	int warpWidth = ofToInt(Settings::instance()->xml.getValue("warped/width"));
	int warpHeight = ofToInt(Settings::instance()->xml.getValue("warped/height"));
	_warped.allocate(warpWidth, warpHeight, OF_IMAGE_GRAYSCALE);
	_warpedMat = ofxCv::toCv(_warped);
	
	cout << "camera width: " << w << endl;
	cout << "camera height: " << h << endl;
	
#ifdef TARGET_RASPBERRY_PI
	cam.setup(w, h, false);
#else
	// TODO: Get device id from settings
	cam.setDeviceID(0);
    cam.setDesiredFrameRate(60);
	cam.setPixelFormat(OF_PIXELS_RGB);
    cam.initGrabber(w, h);
#endif

	// Set the corners for cropping the tracking area.
	_areaSrcPoints.resize(4);
	_areaSrcPoints[0].x = ofToFloat(Settings::instance()->xml.getValue("projection/tl/x"));
	_areaSrcPoints[0].y = ofToFloat(Settings::instance()->xml.getValue("projection/tl/y"));
	_areaSrcPoints[1].x = ofToFloat(Settings::instance()->xml.getValue("projection/tr/x"));
	_areaSrcPoints[1].y = ofToFloat(Settings::instance()->xml.getValue("projection/tr/y"));
	_areaSrcPoints[2].x = ofToFloat(Settings::instance()->xml.getValue("projection/br/x"));
	_areaSrcPoints[2].y = ofToFloat(Settings::instance()->xml.getValue("projection/br/y"));
	_areaSrcPoints[3].x = ofToFloat(Settings::instance()->xml.getValue("projection/bl/x"));
	_areaSrcPoints[3].y = ofToFloat(Settings::instance()->xml.getValue("projection/bl/y"));
	
	// The destination is always going to be the size of the tracking area.
	_areaDstPoints.resize(4);
	_areaDstPoints[0].x = 0;
	_areaDstPoints[0].y = 0;
	_areaDstPoints[1].x = warpWidth;
	_areaDstPoints[1].y = 0;
	_areaDstPoints[2].x = warpWidth;
	_areaDstPoints[2].y = warpHeight;
	_areaDstPoints[3].x = 0;
	_areaDstPoints[3].y = warpHeight;
	
	// Set contour finder settings
	_contourFinder.setThreshold(225);
	_contourFinder.setMinAreaRadius(10);
	_contourFinder.setMaxAreaRadius(100);
	_contourFinder.setSortBySize(true);
}

void Tracker::update(){

#ifndef TARGET_RASPBERRY_PI
		cam.update();
#endif

	if(cam.isFrameNew()){
		cv::Mat homography = cv::findHomography(cv::Mat(_areaSrcPoints), cv::Mat(_areaDstPoints));
		
#ifdef TARGET_RASPBERRY_PI
		if(cam.grab().empty()){
			return;
		}
		cv::Mat frame = cam.grab();
		ofxCv::warpPerspective(frame, _warpedMat, homography, CV_INTER_LINEAR);
		_contourFinder.findContours(_warpedMat);
#else
		_contourFinder.findContours(cam.getPixels());
#endif

		if(_contourFinder.size()){
			_position.x = _contourFinder.getCenter(0).x;
			_position.y = _contourFinder.getCenter(0).y;
		}
	}

	/*
	if(_camera->isFrameNew()){
		
		// Find homography for perspective transformation below.
		cv::Mat homography = cv::findHomography(cv::Mat(_areaSrcPoints), cv::Mat(_areaDstPoints));

		// Convert the incoming image to grayscale as fast as possible.
		//ofxCv::copyGray(_camera->getPixels(), _grayImage);
		
		_grayImage = _camera->getFrame();
		if(_grayImage.empty()){
			return;
		}
		cout << "cv::Mat not empty" << endl;
		
		// Crop the area of interest from the grayscale camera image
		// and put it into the _trackArea variable.
		ofxCv::warpPerspective(_grayImage, _trackArea, homography, CV_INTER_LINEAR);
		
		// Find the contours based on settings above.
		_contourFinder.findContours(_trackArea);
		
		// If at least one contour found, take it and set the position values from it.
		
	}
	*/
}

void Tracker::draw(){
	//ofxCv::drawMat(_trackArea, 0, 0);
	//ofxCv::drawMat(_grayImage, _camera->getWidth(), 0);
	
	#ifdef TARGET_RASPBERRY_PI
	ofxCv::drawMat(_warpedMat, 0, 0, cam.width, cam.height);
	cv::Mat frame = cam.grab();
	ofxCv::drawMat(frame, ofxCv::getWidth(_warpedMat), 0, cam.width, cam.height);
	#else
	cam.draw(0, 0, cam.getWidth(), cam.getHeight());
	#endif
	
	_contourFinder.draw();
}

void Tracker::setTrackArea(vector<ofPoint> & $corners){
	_areaSrcPoints.clear();
	_areaSrcPoints.resize($corners.size());
	for(auto i = 0; i < _areaSrcPoints.size(); ++i){
		_areaSrcPoints[i].x = $corners[i].x;
		_areaSrcPoints[i].y = $corners[i].y;
	}
	
	Settings::instance()->xml.setValue("projection/tl/x", ofToString(_areaSrcPoints[0].x, 0));
	Settings::instance()->xml.setValue("projection/tl/y", ofToString(_areaSrcPoints[0].y, 0));
	Settings::instance()->xml.setValue("projection/tr/x", ofToString(_areaSrcPoints[1].x, 0));
	Settings::instance()->xml.setValue("projection/tr/y", ofToString(_areaSrcPoints[1].y, 0));
	Settings::instance()->xml.setValue("projection/br/x", ofToString(_areaSrcPoints[2].x, 0));
	Settings::instance()->xml.setValue("projection/br/y", ofToString(_areaSrcPoints[2].y, 0));
	Settings::instance()->xml.setValue("projection/bl/x", ofToString(_areaSrcPoints[3].x, 0));
	Settings::instance()->xml.setValue("projection/bl/y", ofToString(_areaSrcPoints[3].y, 0));
}

ofVec2f Tracker::getPosition(){
	return _position;
}

int Tracker::getWidth(){
	#ifdef TARGET_RASPBERRY_PI
	return cam.width;
	#else
	return cam.getWidth();
	#endif
}

int Tracker::getHeight(){
	#ifdef TARGET_RASPBERRY_PI
	return cam.height;
	#else
	return cam.getHeight();
	#endif
}

} // namespace ytr
