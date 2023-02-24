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

	// More settings
	_minSpawnFrequency = ofToFloat(Settings::instance()->xml.findFirst("settings/text/spawn/frequency/min").getValue());
	_maxSpawnFrequency = ofToFloat(Settings::instance()->xml.findFirst("settings/text/spawn/frequency/max").getValue());
	_spawnFrequency = _minSpawnFrequency;
	_lastSpawnTime = 0.0f;
	
	cout << "minSpawnFreq: " << _minSpawnFrequency << endl;
	cout << "maxSpawnFreq: " << _maxSpawnFrequency << endl;
	
	_reactToMouse = ofToBool(Settings::instance()->xml.findFirst("settings/brush/reactToMouse/enable").getValue());

	// Create components
	tracker = Tracker::create();
	projection = Projection::create();
	overlay = Overlay::create();
	brush = Brush::create();
	
	// Register for OSC events
	ofAddListener(OscGate::instance()->events, this, &Application::onOscEvent);
}

void Application::update(){

	if(_reactToMouse){
		brush->setPosition(
	   		ofInterpolateCosine(
		   		brush->getPosition(),
				ofVec2f(ofGetMouseX(), ofGetMouseY()), 0.5f));
	}else{
		brush->setPosition(
	   		ofInterpolateCosine(
		   		brush->getPosition(),
				tracker->getPosition(), 0.5f));
	}
	_mode->update();
	
	// Update OSC connection
	OscGate::instance()->update();
	
	// Get spawn frequency from brush speed
	_spawnFrequency = ofMap(brush->getSpeed(),
							0.0f,
							brush->getMaxSpeed(),
							_minSpawnFrequency,
							_maxSpawnFrequency);
	
	// Add new words to the party depending on the frequency
	float spawnInterval = 1.0f / _spawnFrequency;
	float now = ofGetElapsedTimef();
	float delta = now - _lastSpawnTime;
	if(delta > spawnInterval){
		brush->addWord(Library::instance()->text->getNextWord());
		_lastSpawnTime = now;
	}
}

void Application::draw(){
	_mode->draw();
	
	if(Settings::instance()->debug){
		_gui.draw();
		string info = "fps: " + ofToString(ofGetFrameRate(), 2) +
			"\nspeed: " + ofToString(brush->getSpeed(), 2);
		ofDrawBitmapString(info, 10, ofGetHeight() -20);
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
			#if defined OF_TARGET_OSX
				CGDisplayShowCursor(kCGDirectMainDisplay);
			#else
				ofShowCursor();
			#endif
		}else{
			#if defined OF_TARGET_OSX
				CGDisplayHideCursor(kCGDirectMainDisplay);
			#else
				ofHideCursor();
			#endif
		}
	}
	
	if(key == 'f'){
		ofToggleFullscreen();
	}
	
	if(key == 't'){
		cout << "Adding word" << endl;
		brush->addWord("random");
	}

	// Modes
	if(key == 'c'){
		setMode(Mode::CALIBRATE);
	}else if(key == 'q'){
		setMode(Mode::DEFAULT);
	}else if(key == 'b'){
		setMode(Mode::BLANK);
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
	}else if($name == Mode::BLANK){
		_mode = ModeBlank::instance();
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
	
	string addr = message.getAddress();
	
	if(addr == "/calibrate"){
		setMode(Mode::CALIBRATE);
	}else if(addr == "/cancel"){
		setMode(Mode::DEFAULT);
	}else if(addr == "/point"){
		ofPoint p;
		p.x = message.getArgAsInt(0);
		p.y = message.getArgAsInt(1);
		
		if(_mode == ModeCalibrate::instance()){
			ModeCalibrate::instance()->mousePressed(p.x, p.y, OF_MOUSE_BUTTON_1);
		}
	}else if(addr == "/mode/blank"){
		setMode(Mode::BLANK);
	}else if(addr == "/mode/default"){
		setMode(Mode::DEFAULT);
	}
}

} // namespace ytr
