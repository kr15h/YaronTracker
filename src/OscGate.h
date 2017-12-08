#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

namespace ytr{

class OscGate{
public:
	static shared_ptr<OscGate> instance();
	
	void update();
	
	ofEvent<ofxOscMessage> events;

private:
	static shared_ptr<OscGate> _instance;
	OscGate();
	
	ofxOscReceiver _receiver;

};

} // namespace ytr
