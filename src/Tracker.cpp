#include "Tracker.h"

namespace ytr {

shared_ptr<Tracker> Tracker::create(shared_ptr<Camera> $camera){
	return shared_ptr<Tracker>(new Tracker($camera));
}

Tracker::Tracker(shared_ptr<Camera> $camera){
	_camera = $camera;
	
	// TODO: read values from settings, should be the same as for the cam
	ofImage srcImage;
	srcImage.allocate(_camera->getWidth(), _camera->getHeight(), OF_IMAGE_GRAYSCALE);
	_grayImage = ofxCv::toCv(srcImage);
	
	ofImage dstImage;
	dstImage.allocate(_camera->getWidth(), _camera->getHeight(), OF_IMAGE_GRAYSCALE);
	_trackArea = ofxCv::toCv(dstImage);
	
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
	_areaDstPoints[1].x = _camera->getWidth();
	_areaDstPoints[1].y = 0;
	_areaDstPoints[2].x = _camera->getWidth();
	_areaDstPoints[2].y = _camera->getHeight();
	_areaDstPoints[3].x = 0;
	_areaDstPoints[3].y = _camera->getHeight();
	
	// Set contour finder settings
	_contourFinder.setThreshold(225);
	_contourFinder.setMinAreaRadius(10);
	_contourFinder.setMaxAreaRadius(100);
	_contourFinder.setSortBySize(true);
}

void Tracker::update(){
	if(_camera->isFrameNew()){

		// Find homography for perspective transformation below.
		cv::Mat homography = cv::findHomography(cv::Mat(_areaSrcPoints), cv::Mat(_areaDstPoints));

		// Convert the incoming image to grayscale as fast as possible.
		//ofxCv::copyGray(_camera->getPixels(), _grayImage);
		
		_grayImage = _camera->getFrame();
		
		// Crop the area of interest from the grayscale camera image
		// and put it into the _trackArea variable.
		ofxCv::warpPerspective(_grayImage, _trackArea, homography, CV_INTER_LINEAR);
		
		// Find the contours based on settings above.
		_contourFinder.findContours(_trackArea);
		
		// If at least one contour found, take it and set the position values from it.
		if(_contourFinder.size()){
			_position.x = _contourFinder.getCenter(0).x;
			_position.y = _contourFinder.getCenter(0).y;
		}
	}
}

void Tracker::draw(){
	ofxCv::drawMat(_trackArea, 0, 0);
	ofxCv::drawMat(_grayImage, _camera->getWidth(), 0);
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
	return _camera->getWidth();
}

int Tracker::getHeight(){
	return _camera->getHeight();
}

} // namespace ytr
