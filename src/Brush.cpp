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
	_maxSpeed = 0.0f;
	
	_swarmCircles.resize(5);
	for(auto i = 0; i < _swarmCircles.size(); ++i){
		_swarmCircles[i].angularPosition = 360.0f / (float)_swarmCircles.size() * (float)i;
		_swarmCircles[i].radius = 20.0f;
	}
}

void Brush::update(){
	_rotation += _rotationSpeed * ofGetLastFrameTime();
	
	// Update words
	for(auto i = 0; i < _words.size(); ++i){
		if(_words[i].alpha < 0.0f){
			_words.erase(_words.begin() + i);
			i--;
			continue;
		}
		
		// Calculate x and y speed increase from direction
		float dirHyp = sqrt(pow(_words[i].direction.x, 2.0f) + pow(_words[i].direction.y, 2.0f));
		float dirSin = _words[i].direction.x / dirHyp;
		float dirCos = _words[i].direction.y / dirHyp;
		float xSpeed = _words[i].speed * dirSin;
		float ySpeed = _words[i].speed * dirCos;
		
		_words[i].position =
			ofVec2f(_words[i].position +
			ofVec2f(xSpeed * ofGetLastFrameTime(),
					ySpeed * ofGetLastFrameTime()));
		_words[i].alpha -= 0.01f;
	}
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
	
	// Draw words
	for(auto i = 0; i < _words.size(); ++i){
		ofPushStyle();
		int alphaByte = (int)(_words[i].alpha * 255.0f);
		ofSetColor(255, 255, 255, alphaByte);
		Library::instance()->font.drawStringAsShapes(
		_words[i].text, _words[i].position.x, _words[i].position.y);
		ofPopStyle();
	}
}

void Brush::setPosition(ofVec2f $position){
	_prevPosition = _position;
	_prevPositionTime = ofGetElapsedTimef();
	_direction = $position - _position;
	_position = $position;
}

ofVec2f Brush::getPosition(){
	return _position;
}

float Brush::getSpeed(){
	ofVec2f delta = _position - _prevPosition;
	float speed = sqrt(pow(_position.x, 2.0f) + pow(_position.y, 2.0f));
	if(speed > _maxSpeed){
		_maxSpeed = speed;
	}
	return speed;
}

float Brush::getMaxSpeed(){
	return _maxSpeed;
}

void Brush::addWord(string word){
	Word w;
	w.text = word;
	w.position = _position;
	w.direction = -_direction;
	w.alpha = 1.0f;
	w.speed = ofRandomf() * 50.0f;
	_words.push_back(w);
}

} // namespace ytr
