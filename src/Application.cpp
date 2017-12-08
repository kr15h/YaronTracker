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

	// Setup slider, it is important to load the params before we create components
	_gui.setup("params");
	_gui.add(Settings::instance()->threshold.set("threshold", 240, 0, 255 ));
	_gui.add(Settings::instance()->minAreaRadius.set("minAreaRadius", 10, 0, 100));
	_gui.add(Settings::instance()->maxAreaRadius.set("maxAreaRadius", 10, 0, 100));
	_gui.loadFromFile("params.xml");

	// Create components
	tracker = Tracker::create();
	projection = Projection::create();
	overlay = Overlay::create();
	brush = Brush::create();
	
	// Register for OSC events
	ofAddListener(OscGate::instance()->events, this, &Application::onOscEvent);
}

void Application::update(){
	brush->setPosition(
	   ofInterpolateCosine(
		   brush->getPosition(),
		   tracker->getPosition(), 0.5f));
	_mode->update();
	
	// Update OSC connection
	OscGate::instance()->update();
}

void Application::draw(){
	_mode->draw();
	
	if(Settings::instance()->debug){
		_gui.draw();
		ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate(), 2), 10, ofGetHeight() -10);
	}
}

void Application::exit(){
	Settings::instance()->save();
	_gui.saveToFile("params.xml");
}

void Application::keyPressed(int key){
	_mode->keyPressed(key);
	
	if(ofGetKeyPressed(OF_KEY_COMMAND) && key == 'p'){
		saveCameraSnapshot("test.jpg");
	}
	
	if(key == 'd'){
		Settings::instance()->debug = !Settings::instance()->debug;
		if(Settings::instance()->debug){
			#ifdef TARGET_RASPBERRY_PI
				ofShowCursor();
			#else
				CGDisplayShowCursor(kCGDirectMainDisplay);
			#endif
		}else{
			#ifdef TARGET_RASPBERRY_PI
				ofHideCursor();
			#else
				CGDisplayHideCursor(kCGDirectMainDisplay);
			#endif
		}
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
	ofImage snap;
	ofxCv::toOf(tracker->getFrame(), snap);
	snap.update();
	snap.save(filename, OF_IMAGE_QUALITY_MEDIUM);
	cout << "Saved image with name " << filename << endl;
}

void Application::onOscEvent(ofxOscMessage & message){
	cout << "onOscEvent: " << message.getAddress() << endl;
}

} // namespace ytr
