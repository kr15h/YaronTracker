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
	tracker = Tracker::create();
	projection = Projection::create();
	overlay = Overlay::create();
	brush = Brush::create();
}

void Application::update(){
	brush->setPosition(
	   ofInterpolateCosine(
		   brush->getPosition(),
		   tracker->getPosition(), 0.5f));
	_mode->update();
}

void Application::draw(){
	_mode->draw();
	
	// Draw debug data
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate(), 2), 10, 20);
}

void Application::exit(){
	Settings::instance()->save();
}

void Application::keyPressed(int key){
	_mode->keyPressed(key);
	
	if(ofGetKeyPressed(OF_KEY_COMMAND) && key == 'p'){
		saveCameraSnapshot("test.jpg");
	}
	
	if(key == 'd'){
		Settings::instance()->debug = !Settings::instance()->debug;
	}
	
	if(key == 'f'){
		ofToggleFullscreen();
	}
}

void Application::mousePressed(int x, int y, int button){
	_mode->mousePressed(x, y, button);
}

void Application::setMode(Mode::Name $name){
	if($name == Mode::DEFAULT){
		_mode = ModeDefault::instance();
	}else if($name == Mode::CALIBRATE){
		overlay->showCorner(Overlay::TOP_LEFT);
		_mode = ModeCalibrate::instance();
	}
}

void Application::saveCameraSnapshot(string filename){
	/*
	ofImage snap;
	ofxCv::toOf(camera->getFrame(), snap);
	snap.update();
	snap.save(filename);
	cout << "Saved image with name " << filename << endl;
	*/
}

} // namespace ytr
