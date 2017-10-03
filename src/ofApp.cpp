#include "ofApp.h"

void ofApp::setup(){
	ofSetVerticalSync(true);
	_application = ytr::YaronTracker::create();
}

void ofApp::update(){
	_application->update();
}

void ofApp::draw(){
	_application->draw();
}
