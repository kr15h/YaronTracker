#pragma once

#include "ofMain.h"

#include "Mode.h"
#include "ModeDefault.h"
#include "ModeCalibrate.h"
#include "ModeBlank.h"

#include "Tracker.h"
#include "Projection.h"
#include "Overlay.h"
#include "Brush.h"
#include "Library.h"

#include "Settings.h"
#include "OscGate.h"

#include "ofxGui.h"
#include "ofxOscMessage.h"

namespace ytr{

class Application{
public:
	static shared_ptr<Application> instance();
	
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

	void setMode(Mode::Name $name);
	void saveCameraSnapshot(string filename);
	void onOscEvent(ofxOscMessage & message);

	shared_ptr<Tracker> tracker;
	shared_ptr<Projection> projection;
	shared_ptr<Overlay> overlay;
	shared_ptr<Brush> brush;

private:
	static shared_ptr<Application> _instance;
	Application();
	
	shared_ptr<Mode> _mode;
	
	ofxPanel _gui;
	
	float _spawnFrequency;
	float _minSpawnFrequency;
	float _maxSpawnFrequency;
	float _lastSpawnTime;
	
	bool _reactToMouse;
};

} // namespace ytr
