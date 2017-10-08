#include "ModeDefault.h"

namespace ytr {

shared_ptr<Mode> ModeDefault::_instance = 0;

shared_ptr<Mode> ModeDefault::instance(){
	if(_instance == 0){
		_instance = shared_ptr<ModeDefault>(new ModeDefault());
	}
	return _instance;
}

ModeDefault::ModeDefault(){
	cout << "ModeDefault" << endl;
}

void ModeDefault::update(){
	Application::instance()->tracker->update();
	Application::instance()->brush->update();
}

void ModeDefault::draw(){
	if(Settings::instance()->debug){
		Application::instance()->tracker->draw();
		Application::instance()->projection->draw();
	}
	Application::instance()->brush->draw();
}

void ModeDefault::keyPressed(int key){
	if(key == 'c'){
		Application::instance()->setMode(Mode::CALIBRATE);
	}
}

} // namespace ytr
