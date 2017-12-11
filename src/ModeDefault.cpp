#include "ModeDefault.h"

namespace ytr {

shared_ptr<Mode> ModeDefault::_instance = 0;

shared_ptr<Mode> ModeDefault::instance(){
	if(_instance == 0){
		_instance = shared_ptr<ModeDefault>(new ModeDefault());
	}
	return _instance;
}

ModeDefault::ModeDefault(){
	cout << "ModeDefault" << endl;
}

void ModeDefault::update(){
	Application::instance()->tracker->update();
	Application::instance()->brush->update();
}

void ModeDefault::draw(){
	if(Settings::instance()->debug){
		Application::instance()->tracker->draw();
		Application::instance()->projection->draw();
		
		// Draw the direction vector of current movement
		ofPushStyle();
		ofVec2f dir = Application::instance()->brush->getDirection();
		ofPushMatrix();
		ofTranslate(ofGetWidth() - 100, 100);
		ofDrawLine(0, 0, dir.x * 90, dir.y * 90);
		ofPopMatrix();
		ofPopStyle();
	}
	Application::instance()->brush->draw();
}

void ModeDefault::keyPressed(int key){
	if(key == 'c' && Settings::instance()->debug){
		Application::instance()->setMode(Mode::CALIBRATE);
	}
}

} // namespace ytr
