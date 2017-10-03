#include "ofApp.h"

void ofApp::setup(){
	ofSetVerticalSync(true);
	app = ytr::Application::create();
}

void ofApp::update(){
	app->update();
}

void ofApp::draw(){
	app->draw();
}
