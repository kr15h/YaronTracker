#include "Brush.h"

namespace ytr {

shared_ptr<Brush> Brush::create(){
	return shared_ptr<Brush>(new Brush);
}

Brush::Brush(){
	_prevPosition = ofVec2f(0, 0);
	_position = ofVec2f(0, 0);
	
	_rotation = 0.0f;
	_rotationSpeed = 5.0f;
	
	_swarmCircles.resize(5);
	for(auto i = 0; i < _swarmCircles.size(); ++i){
		_swarmCircles[i].angularPosition = 360.0f / (float)_swarmCircles.size() * (float)i;
		_swarmCircles[i].radius = 20.0f;
	}
}

void Brush::update(){
	_rotation += _rotationSpeed * ofGetLastFrameTime();
}

void Brush::draw(){
	ofPushMatrix();
	ofTranslate(_position.x, _position.y);
	ofRotateZ(_rotation);

	ofPushStyle();
	ofSetColor(255, 255, 255);
	ofNoFill();
	ofSetLineWidth(3);
	
	// Draw circle with variable radius,
	ofDrawCircle(0, 0, 100);
	ofPopStyle();
	
	// Draw swarm circles on top
	ofFill();
	for(auto i = 0; i < _swarmCircles.size(); ++i){
		ofPushMatrix();
		ofRotateZ(_swarmCircles[i].angularPosition);
		ofDrawCircle(100, 0, _swarmCircles[i].radius);
		ofPopMatrix();
	}
	
	ofPopMatrix();
}

void Brush::setPosition(ofVec2f $position){
	_prevPosition = _position;
	_prevPositionTime = ofGetElapsedTimef();
	_position = $position;
}

ofVec2f Brush::getPosition(){
	return _position;
}

} // namespace ytr
