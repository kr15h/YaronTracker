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
	camera = CameraFactory::create();
	tracker = Tracker::create(camera);
	projection = Projection::create();
	overlay = Overlay::create();
}

void Application::update(){
	_mode->update();
}

void Application::draw(){
	_mode->draw();
	
	ofVec2f pos = tracker->getPosition();
	ofVec2f posNorm = pos / ofVec2f(tracker->getWidth(), tracker->getHeight());
	
	// Draw position
	ofPushStyle();
	ofSetColor(0, 255, 255);
	ofDrawLine(0, posNorm.y * ofGetHeight(), ofGetWidth(), posNorm.y * ofGetHeight());
	ofDrawLine(posNorm.x * ofGetWidth(), 0, posNorm.x * ofGetWidth(), ofGetHeight());
	ofPopStyle();
	
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
	ofImage snap;
	ofxCv::toOf(camera->getFrame(), snap);
	snap.update();
	snap.save(filename);
	cout << "Saved image with name " << filename << endl;
}

} // namespace ytr
