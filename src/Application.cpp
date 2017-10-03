#include "Application.h"

namespace ytr{

shared_ptr<Application> Application::create(){
	return shared_ptr<Application>(new Application());
}

Application::Application(){
	_camera = Camera::create();
	_tracker = Tracker::create(_camera);
}

void Application::update(){
	_camera->update();
	_tracker->update();
}

void Application::draw(){
	//_camera->draw();
	_tracker->drawGrayImage();
	_tracker->drawContours();
	//_tracker->draw();
	
	ofPushStyle();
	ofSetColor(0, 255, 255);
	ofDrawLine(0, _tracker->getPosition().y, ofGetWidth(), _tracker->getPosition().y);
	ofDrawLine(_tracker->getPosition().x, 0, _tracker->getPosition().x, ofGetHeight());
	ofPopStyle();
}

} // namespace ytr
