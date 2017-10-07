#include "ofApp.h"

void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetEscapeQuitsApp(false);
	#ifdef TARGET_RASPBERRY_PI
		ofSetFullscreen(true);
	#endif
}

void ofApp::update(){
	Application::instance()->update();
}

void ofApp::draw(){
	Application::instance()->draw();
}

void ofApp::exit(){
	Application::instance()->exit();
}

void ofApp::keyPressed(int key){
	Application::instance()->keyPressed(key);
	if(ofGetKeyPressed(OF_KEY_COMMAND)){
		if(key == 's'){
			Settings::instance()->save();
		}
	}
}

void ofApp::mousePressed(int x, int y, int button){
	Application::instance()->mousePressed(x, y, button);
}
