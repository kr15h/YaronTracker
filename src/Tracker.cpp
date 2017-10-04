#include "Tracker.h"

namespace ytr {

shared_ptr<Tracker> Tracker::create(shared_ptr<Camera> $camera){
	return shared_ptr<Tracker>(new Tracker($camera));
}

Tracker::Tracker(shared_ptr<Camera> $camera){
	_camera = $camera;
	
	// TODO: load saved corners from file, create default otherwise
	for(auto i = 0; i < 4; ++i){
		ofVec2f corner;
		_corners.push_back(corner);
	}
	
	_corners[0].x = 0;
	_corners[0].y = 0;
	_corners[1].x = _camera->getWidth();
	_corners[1].y = 0;
	_corners[2].x = _camera->getWidth();
	_corners[2].y = _camera->getHeight();
	_corners[3].x = 0;
	_corners[3].y = _camera->getHeight();
}

void Tracker::update(){
	// get and track blobs in camera image
	
	bool frameIsNew = _camera->isFrameNew();
	
	if(frameIsNew){
		_colorImg.setFromPixels(_camera->getPixels());
		
		_grayImage = _colorImg;
		_grayImage.warpPerspective(_corners[0], _corners[1], _corners[2], _corners[3]);
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
}

ofVec2f Tracker::getPosition(){
	return _position;
}

} // namespace ytr
