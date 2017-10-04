#include "ModeCalibrate.h"

namespace ytr {

shared_ptr<Mode> ModeCalibrate::_instance = 0;

shared_ptr<Mode> ModeCalibrate::instance(){
	if(_instance == 0){
		_instance = shared_ptr<ModeCalibrate>(new ModeCalibrate());
	}
	return _instance;
}

ModeCalibrate::ModeCalibrate(){
	cout << "ModeCalibrate" << endl;
}

void ModeCalibrate::update(){
	Application::instance()->camera->update();
}

void ModeCalibrate::draw(){
	Application::instance()->camera->draw();

	ofPushStyle();
	ofNoFill();
	ofSetLineWidth(2);
	for(auto i = 0; i < _corners.size(); ++i){
		ofDrawCircle(_corners[i].x, _corners[i].y, 5);
	}
	ofPopStyle();

	string textToDraw = "Calibrate mode";
	textToDraw += "\nSelect corner " + ofToString(_corners.size() + 1);
	ofDrawBitmapString(textToDraw, 10, 20);
}

void ModeCalibrate::keyPressed(int key){
	if(key == OF_KEY_ESC){
		_corners.clear();
		Application::instance()->setMode(Mode::DEFAULT);
	}
}

void ModeCalibrate::mousePressed(int x, int y, int button){
	if(button == OF_MOUSE_BUTTON_1){
		ofVec2f corner;
		corner.x = x;
		corner.y = y;
		_corners.push_back(corner);
	}
	
	if(_corners.size() == 4){
		Application::instance()->setTrackArea(_corners);
		_corners.clear();
		Application::instance()->setMode(Mode::DEFAULT);
	}
}

} // namespace ytr
