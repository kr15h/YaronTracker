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
	Application::instance()->camera->update();
	Application::instance()->tracker->update();
}

void ModeDefault::draw(){
	Application::instance()->tracker->draw();
	ofDrawBitmapString("Default mode", 10, 20);
}

void ModeDefault::keyPressed(int key){
	if(key == 'c'){
		Application::instance()->setMode(Mode::CALIBRATE);
	}
}

} // namespace ytr
