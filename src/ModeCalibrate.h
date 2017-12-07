#pragma once

#include "ofMain.h"
#include "Mode.h"
#include "Application.h"
#include "Projection.h"

// To save frames on disk for the web calibrator
#define CAM_SNAPSHOT_INTERVAL 0.5f

namespace ytr {

class ModeCalibrate : public Mode{
public:
	static shared_ptr<Mode> instance();
	
	void update();
	void draw();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	
private:
	static shared_ptr<Mode> _instance;
	ModeCalibrate();
	
	void showCorner();
	
	vector<ofPoint> _corners;
	ofColor _color;
	
	float _lastSnapshotTime;
	float _snapshotInterval;
};

} // namespace ytr
