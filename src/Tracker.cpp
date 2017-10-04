#include "Tracker.h"

namespace ytr {

shared_ptr<Tracker> Tracker::create(shared_ptr<Camera> $camera){
	return shared_ptr<Tracker>(new Tracker($camera));
}

Tracker::Tracker(shared_ptr<Camera> $camera){
	_camera = $camera;
	
	// Set initial width and height of the surface being tracked.
	// Later we replace this with the perspective-corrected width and height.
	_width = ofToInt(Settings::instance()->xml.getValue("tracker/width"));
	_height = ofToInt(Settings::instance()->xml.getValue("tracker/height"));
	_updateDimensions = false;
	
	_corners.resize(4);
	_corners[0].x = ofToFloat(Settings::instance()->xml.getValue("projection/tl/x"));
	_corners[0].y = ofToFloat(Settings::instance()->xml.getValue("projection/tl/y"));
	_corners[1].x = ofToFloat(Settings::instance()->xml.getValue("projection/tr/x"));
	_corners[1].y = ofToFloat(Settings::instance()->xml.getValue("projection/tr/y"));
	_corners[2].x = ofToFloat(Settings::instance()->xml.getValue("projection/br/x"));
	_corners[2].y = ofToFloat(Settings::instance()->xml.getValue("projection/br/y"));
	_corners[3].x = ofToFloat(Settings::instance()->xml.getValue("projection/bl/x"));
	_corners[3].y = ofToFloat(Settings::instance()->xml.getValue("projection/bl/y"));
}

void Tracker::update(){
	// get and track blobs in camera image
	
	bool frameIsNew = _camera->isFrameNew();
	
	if(frameIsNew){
		_colorImg.setFromPixels(_camera->getPixels());
		
		_grayImage = _colorImg;
		_grayImage.warpPerspective(_corners[0], _corners[1], _corners[2], _corners[3]);
		
		// Here we adjust the tracker width and height to be able to get normalized value.
		_width = _grayImage.getWidth();
		_height = _grayImage.getHeight();
		
		if(_updateDimensions){
			Settings::instance()->xml.setValue("tracker/width", ofToString(_width, 0));
			Settings::instance()->xml.setValue("tracker/height", ofToString(_height, 0));
			_updateDimensions = false;
		}
		
		_threshImage = _grayImage;
		
		// Consider areas that are brighter than N in the range from 0 (black) and 255 (white)
		_threshImage.threshold(225);
		
		// input, min area, max area, number of blobs, find holes
		_contourFinder.findContours(_threshImage, 10, (_camera->getWidth()*_camera->getHeight())/3, 1, false);
		
		if(_contourFinder.blobs.size()){
			_position.x = _contourFinder.blobs[0].centroid.x;
			_position.y = _contourFinder.blobs[0].centroid.y;
		}
	}
}

void Tracker::drawGrayImage(){
	_grayImage.draw(0, 0);
}

void Tracker::drawContours(){
	_contourFinder.draw();
}

void Tracker::draw(){
	_grayImage.draw(0, 0);
	_threshImage.draw(_grayImage.width, 0);
	_contourFinder.draw();
}

void Tracker::setTrackArea(vector<ofPoint> & $corners){
	_corners = $corners;
	
	Settings::instance()->xml.setValue("projection/tl/x", ofToString(_corners[0].x, 0));
	Settings::instance()->xml.setValue("projection/tl/y", ofToString(_corners[0].y, 0));
	Settings::instance()->xml.setValue("projection/tr/x", ofToString(_corners[1].x, 0));
	Settings::instance()->xml.setValue("projection/tr/y", ofToString(_corners[1].y, 0));
	Settings::instance()->xml.setValue("projection/br/x", ofToString(_corners[2].x, 0));
	Settings::instance()->xml.setValue("projection/br/y", ofToString(_corners[2].y, 0));
	Settings::instance()->xml.setValue("projection/bl/x", ofToString(_corners[3].x, 0));
	Settings::instance()->xml.setValue("projection/bl/y", ofToString(_corners[3].y, 0));
	
	_updateDimensions = true;
}

ofVec2f Tracker::getPosition(){
	return _position;
}

int Tracker::getWidth(){
	return _width;
}

int Tracker::getHeight(){
	return _height;
}

} // namespace ytr
