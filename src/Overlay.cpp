#include "Overlay.h"

namespace ytr {

shared_ptr<Overlay> Overlay::create(){
	return shared_ptr<Overlay>(new Overlay);
}

Overlay::Overlay(){
	_cornerToShow = NONE;
}

void Overlay::draw(){

	// Decide on rotation and gl translation depending on corner to show
	float rotation;
	ofVec2f translation;
	
	switch(_cornerToShow){
		case TOP_LEFT:
			rotation = 0;
			translation = ofVec2f(0, 0);
			break;
		case TOP_RIGHT:
			rotation = 90;
			translation = ofVec2f(ofGetWidth(), 0);
			break;
		case BOTTOM_RIGHT:
			rotation = 180;
			translation = ofVec2f(ofGetWidth(), ofGetHeight());
			break;
		case BOTTOM_LEFT:
			rotation = 270;
			translation = ofVec2f(0, ofGetHeight());
			break;
		default:
			break;
	}
	
	// Draw image with transformation
	if(_cornerToShow != NONE){
		ofPushMatrix();
		ofTranslate(translation.x, translation.y);
		ofRotate(rotation);
		
		// Make the arrow image transparent so we can
		// still see the camera image and where the corners are.
		ofSetColor(255, 255, 255, 175);
		Library::instance()->images.arrow.draw(0, 0);
		ofPopMatrix();
	}
	
	// draw a thick white border
	ofPushStyle();
	ofSetColor(255);
	ofNoFill();
	ofSetLineWidth(4);
	ofDrawRectangle(4, 4, ofGetWidth()-8, ofGetHeight()-8);
	ofPopStyle();
}

void Overlay::showCorner(Corner $corner){
	_cornerToShow = $corner;
}

} // namespace ytr
