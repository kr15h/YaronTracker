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
	float angle;
	bool hasFadedIn;
};

class Brush{
public:
	static shared_ptr<Brush> create();
	
	void update();
	void draw();
	
	void setPosition(ofVec2f $position);
	ofVec2f getPosition();
	ofVec2f getDirection();
	
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
	float _speedFactor;
	float _pullSwarmFactor;
	float _alphaFadeInSpeed; // Factor per sedond
	float _alphaFadeOutSpeed; // Factor per sedond
	float _spawnDistanceFromOrigin; // In pixels
	
	bool _enableTextAngle;
	bool _enablePullSwarm;
	
	vector<SwarmCircle> _swarmCircles;
	vector<Word> _words;
};

} // namespace ytr
