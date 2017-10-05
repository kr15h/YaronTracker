#include "Projection.h"

namespace ytr {

shared_ptr<Projection> Projection::create(){
	return shared_ptr<Projection>(new Projection());
}

Projection::Projection(){
	_cornerToHighlight = NONE;
}

void Projection::update(){
	// Do some swarm math
}

void Projection::draw(){
	if(_cornerToHighlight == NONE){
		// Draw the swarm
	}else{
		// Draw white background
		ofPushStyle();
		ofSetColor(255);
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		ofPopStyle();
	}
	
	float rotation;
	ofImage & image = Library::instance()->images.arrow;
	
	// Highlight the corner
	ofVec2f position;
	switch (_cornerToHighlight) {
		case TOP_LEFT:
			position = ofVec2f(0,0);
			rotation = 0;
			break;
		case TOP_RIGHT:
			position = ofVec2f(ofGetWidth(), 0);
			rotation = 90;
			break;
		case BOTTOM_RIGHT:
			position = ofVec2f(ofGetWidth(), ofGetHeight());
			rotation = 180;
			break;
		case BOTTOM_LEFT:
			position = ofVec2f(0, ofGetHeight());
			rotation = 270;
			break;
		case NONE:
		default:
			position = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
			rotation = 0;
			break;
	}
	
	if(_cornerToHighlight != NONE){
		ofPushStyle();
		ofSetLineWidth(10);
		ofSetColor(0, 255, 255);
		ofDrawLine(0, position.y, ofGetWidth(), position.y);
		ofDrawLine(position.x, 0, position.x, ofGetHeight());
		ofPopStyle();
		
		ofPushMatrix();
		ofTranslate(position.x, position.y);
		ofRotate(rotation);
		image.draw(0, 0);
		ofPopMatrix();
	}
}

void Projection::highlightCorner(ytr::Projection::Corner $corner){
	_cornerToHighlight = $corner;
}

} // namespace ytr
