#include "ofApp.h"

void ofApp::setup(){
	ofSetVerticalSync(true);
}

void ofApp::update(){
	YaronTracker::instance()->update();
}

void ofApp::draw(){
	YaronTracker::instance()->draw();
}
