#include "Application.h"

namespace ytr{

shared_ptr<Application> Application::_instance = 0;

shared_ptr<Application> Application::instance(){
	if(_instance == 0){
		_instance = shared_ptr<Application>(new Application);
	}
	return _instance;
}

Application::Application(){

	// Set default mode
	_mode = ModeDefault::instance();

	// Create components
	camera = Camera::create();
	tracker = Tracker::create(camera);
	projection = Projection::create();
}

void Application::update(){
	_mode->update();
}

void Application::draw(){
	_mode->draw();
	
	// Draw position
	ofPushStyle();
	ofSetColor(0, 255, 255);
	ofDrawLine(0, tracker->getPosition().y, ofGetWidth(), tracker->getPosition().y);
	ofDrawLine(tracker->getPosition().x, 0, tracker->getPosition().x, ofGetHeight());
	ofPopStyle();
}

void Application::keyPressed(int key){
	_mode->keyPressed(key);
}

void Application::mousePressed(int x, int y, int button){
	_mode->mousePressed(x, y, button);
}

void Application::setMode(Mode::Name $name){
	if($name == Mode::DEFAULT){
		_mode = ModeDefault::instance();
	}else if($name == Mode::CALIBRATE){
		projection->highlightCorner(Projection::TOP_LEFT);
		_mode = ModeCalibrate::instance();
	}
}

} // namespace ytr
