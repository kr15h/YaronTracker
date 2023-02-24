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
	_minSpeed = ofToFloat(Settings::instance()->xml.findFirst("settings/brush/speed/min").getValue());
	_maxSpeed = ofToFloat(Settings::instance()->xml.findFirst("settings/brush/speed/max").getValue());
	_speed = _minSpeed;
	_speedFactor = ofToFloat(Settings::instance()->xml.findFirst("settings/text/spawn/speed/factor").getValue());
	_pullSwarmFactor = ofToFloat(Settings::instance()->xml.findFirst("settings/brush/pullSwarm/factor").getValue());
	_alphaFadeInSpeed = ofToFloat(Settings::instance()->xml.findFirst("settings/text/alpha/fade/in/speed").getValue());
	_alphaFadeOutSpeed = ofToFloat(Settings::instance()->xml.findFirst("settings/text/alpha/fade/out/speed").getValue());
	_spawnDistanceFromOrigin =
		ofToFloat(Settings::instance()->xml.findFirst("settings/text/spawn/distanceFromOrigin").getValue());
	
	_enableTextAngle = ofToBool(Settings::instance()->xml.findFirst("settings/text/spawn/angle/enable").getValue());
	_enablePullSwarm = ofToBool(Settings::instance()->xml.findFirst("settings/brush/pullSwarm/enable").getValue());
	_showCircle = ofToBool(Settings::instance()->xml.findFirst("settings/brush/showCircle").getValue());
	
	//if(_showCircle){
		_swarmCircles.resize(5);
		for(auto i = 0; i < _swarmCircles.size(); ++i){
			_swarmCircles[i].angularPosition = 360.0f / (float)_swarmCircles.size() * (float)i;
			_swarmCircles[i].radius = 20.0f;
		}
	//}
}

void Brush::update(){
	//if(_showCircle){
		_rotation += _rotationSpeed * ofGetLastFrameTime();
	//}
	
	// Calculate current speed of the brush in pixels per second
	ofVec2f delta = _position - _prevPosition;
	_speed = sqrt(pow(delta.x, 2.0f) + pow(delta.y, 2.0f)) / ofGetLastFrameTime();
	if(_speed > _maxSpeed){
		_speed = _maxSpeed;
	}

	// Reset _prevPosition after speed calculation
	_prevPosition = _position;
	
	// Calculate alpha decay step
	float alphaFadeInStep = _alphaFadeInSpeed * ofGetLastFrameTime();
	float alphaFadeOutStep = _alphaFadeOutSpeed * ofGetLastFrameTime();
	
	// Update words
	for(auto i = 0; i < _words.size(); ++i){
		if(_words[i].alpha < 0.0f && _words[i].hasFadedIn){
			_words.erase(_words.begin() + i);
			i--;
			continue;
		}else if(_words[i].alpha >= 1.0f){
			_words[i].hasFadedIn = true;
			_words[i].alpha = 1.0f;
		}

		// Calculate x and y speed increase from direction
		float dirHyp = sqrt(pow(_words[i].direction.x, 2.0f) + pow(_words[i].direction.y, 2.0f));
		float dirSin = _words[i].direction.x / dirHyp;
		float dirCos = _words[i].direction.y / dirHyp;
		float xSpeed = _words[i].speed * dirSin * ofGetLastFrameTime();
		float ySpeed = _words[i].speed * dirCos * ofGetLastFrameTime();
		
		_words[i].position += ofVec2f(xSpeed, ySpeed);
		
		if(_enablePullSwarm){
		 	_words[i].position = ofInterpolateCosine(
		   		_words[i].position,
				_words[i].position + (_speed * ofGetLastFrameTime()),
				_pullSwarmFactor);
		}
		
		if(_words[i].hasFadedIn){
			_words[i].alpha -= alphaFadeOutStep;
		}else{
			_words[i].alpha += alphaFadeInStep;
		}
		
	}
}

void Brush::draw(){
	//if(_showCircle){
		ofPushMatrix();
		ofTranslate(_position.x, _position.y);
		ofRotateZ(_rotation);

		ofPushStyle();
		ofSetColor(255, 255, 255);
		ofNoFill();
		ofSetLineWidth(3);
	
		// Draw circle with variable radius,
		ofDrawCircle(0, 0, _spawnDistanceFromOrigin);
		ofPopStyle();
	
		// Draw swarm circles on top
		ofFill();
		for(auto i = 0; i < _swarmCircles.size(); ++i){
			ofPushMatrix();
			ofRotateZ(_swarmCircles[i].angularPosition);
			ofDrawCircle(_spawnDistanceFromOrigin, 0, _swarmCircles[i].radius);
			ofPopMatrix();
		}
	
		ofPopMatrix();
	//}
	
	// Draw words
	// for(auto i = 0; i < _words.size(); ++i){
	// 	ofPushStyle();
	// 	int alphaByte = (int)(_words[i].alpha * 255.0f);
	// 	ofSetColor(255, 255, 255, alphaByte);
		
	// 	ofPushMatrix();
		
	// 	Draw text from center
	// 	ofRectangle box = Library::instance()->font.getStringBoundingBox(_words[i].text, 0, 0);
	// 	ofTranslate(_words[i].position.x, _words[i].position.y);
		
	// 	if(_enableTextAngle){
	// 		ofRotate(_words[i].angle, 0, 0, 1);
	// 	}
		
	// 	ofTranslate(-(box.width / 2.0f), (box.height / 2.0f));
	// 	Library::instance()->font.drawStringAsShapes(_words[i].text, 0, 0);
	// 	ofDrawCircle(0, 0, 10);
		
	// 	ofPopMatrix();
		
	// 	ofPopStyle();
	// }
}

void Brush::setPosition(ofVec2f $position){
	_prevPosition = _position;
	_direction = ($position - _position).getNormalized();
	_position = $position;
}

ofVec2f Brush::getPosition(){
	return _position;
}

ofVec2f Brush::getDirection(){
	return _direction;
}

float Brush::getSpeed(){
	return _speed;
}

float Brush::getMaxSpeed(){
	return _maxSpeed;
}

void Brush::addWord(string word){
	Word w;
	w.hasFadedIn = false;
	w.text = word;
	w.position = _position + (_direction.getNormalized() * _spawnDistanceFromOrigin);
	w.direction = _direction;
	
	float hyp = sqrt(pow(_direction.x, 2.0f) + pow(_direction.y, 2.0f));
	float sin = _direction.y / hyp;
	float angle = ofRadToDeg(sin);
	
	if(_direction.x > 0 && _direction.y > 0){
		w.angle = angle + 90;
	}
	
	if(_direction.x < 0 && _direction.y > 0){
		w.angle = 270 - angle;
	}
	
	if(_direction.x < 0 && _direction.y < 0){
		w.angle = 270 - angle;
	}
	
	if(_direction.x > 0 && _direction.y < 0){
		w.angle = angle + 90;
	}

	w.alpha = 0.0f;
	w.speed = getSpeed() * _speedFactor;
	_words.push_back(w);
}

} // namespace ytr
