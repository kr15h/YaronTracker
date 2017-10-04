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
	// Draw the swarm
	
	// Highlight the corner
	ofVec2f position;
	switch (_cornerToHighlight) {
		case TOP_LEFT:
			position = ofVec2f(0,0);
			break;
		case TOP_RIGHT:
			position = ofVec2f(ofGetWidth(), 0);
			break;
		case BOTTOM_RIGHT:
			position = ofVec2f(ofGetWidth(), ofGetHeight());
			break;
		case BOTTOM_LEFT:
			position = ofVec2f(0, ofGetHeight());
			break;
		case NONE:
		default:
			position = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
			break;
	}
	
	if(_cornerToHighlight != NONE){
		ofPushStyle();
		ofSetLineWidth(10);
		ofSetColor(0, 255, 255);
		ofDrawLine(0, position.y, ofGetWidth(), position.y);
		ofDrawLine(position.x, 0, position.x, ofGetHeight());
		ofPopStyle();
	}
}

void Projection::highlightCorner(ytr::Projection::Corner $corner){
	_cornerToHighlight = $corner;
}

} // namespace ytr
