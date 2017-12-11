#pragma once

// Brush that accepts tracker position and highlights where
// the tracked point is on the stage.

#include "ofMain.h"
#include "Library.h"
#include "Settings.h"

namespace ytr {

struct SwarmCircle{
	float angularPosition;
	float radius;
};

struct Word{
	string text;
	ofVec2f position;
	ofVec2f direction;
	float speed;
	float alpha;
};

class Brush{
public:
	static shared_ptr<Brush> create();
	
	void update();
	void draw();
	
	void setPosition(ofVec2f $position);
	ofVec2f getPosition();
	
	// Returns speed in pixels per second
	float getSpeed();
	float getMaxSpeed();
	
	// Swarming words
	void addWord(string word);
	
private:
	Brush();
	
	ofVec2f _prevPosition;
	ofVec2f _position;
	ofVec2f _direction;
	
	float _rotation;
	float _rotationSpeed; // degrees per second
	float _speed; // pixels per second
	float _minSpeed;
	float _maxSpeed;
	
	vector<SwarmCircle> _swarmCircles;
	vector<Word> _words;
};

} // namespace ytr
