#include "Tracker.h"

namespace ytr {

shared_ptr<Tracker> Tracker::create(shared_ptr<Camera> $camera){
	return shared_ptr<Tracker>(new Tracker($camera));
}

Tracker::Tracker(shared_ptr<Camera> $camera){
	_camera = $camera;
}

void Tracker::update(){
	// get and track blobs in camera image
	
	bool frameIsNew = _camera->isFrameNew();
	
	if(frameIsNew){
		_colorImg.setFromPixels(_camera->getPixels());
		_grayImage = _colorImg;
		
		// Consider areas that are brighter than N in the range from 0 (black) and 255 (white)
		_grayImage.threshold(225);
		
		// input, min area, max area, number of blobs, find holes
		_contourFinder.findContours(_grayImage, 10, (_camera->getWidth()*_camera->getHeight())/3, 1, false);
		
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
	// draw contours
	_contourFinder.draw();
}

ofVec2f Tracker::getPosition(){
	return _position;
}

} // namespace ytr
