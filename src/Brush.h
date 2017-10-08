#pragma once

// Brush that accepts tracker position and highlights where
// the tracked point is on the stage.

#include "ofMain.h"

namespace ytr {

struct SwarmCircle{
	float angularPosition;
	float radius;
};

class Brush{
public:
	static shared_ptr<Brush> create();
	
	void update();
	void draw();
	
	void setPosition(ofVec2f $position);
	ofVec2f getPosition();
	
private:
	Brush();
	
	ofVec2f _prevPosition;
	ofVec2f _position;
	
	float _rotation;
	float _rotationSpeed; // degrees per second
	float _prevPositionTime;
	
	vector<SwarmCircle> _swarmCircles;
};

} // namespace ytr
