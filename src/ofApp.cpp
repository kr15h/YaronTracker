#include "ofApp.h"

void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetEscapeQuitsApp(false);
}

void ofApp::update(){
	Application::instance()->update();
}

void ofApp::draw(){
	Application::instance()->draw();
}

void ofApp::keyPressed(int key){
	Application::instance()->keyPressed(key);
}

void ofApp::mousePressed(int x, int y, int button){
	Application::instance()->mousePressed(x, y, button);
}
