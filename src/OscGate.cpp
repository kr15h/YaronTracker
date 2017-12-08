#include "OscGate.h"

namespace ytr{

shared_ptr<OscGate> OscGate::_instance = 0;

shared_ptr<OscGate> OscGate::instance(){
	if(_instance == 0){
		_instance = shared_ptr<OscGate>(new OscGate);
	}
	return _instance;
}

OscGate::OscGate(){
	_receiver.setup(12345);
}

void OscGate::update(){
	while(_receiver.hasWaitingMessages()){
		ofxOscMessage msg;
		_receiver.getNextMessage(msg);
		ofNotifyEvent(events, msg);
	}
}

} // namespace ytr
