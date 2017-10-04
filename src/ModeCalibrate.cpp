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
	
	// Set color according to corners set
	if(_corners.size() == 4){
		_color = ofColor(255, 255, 0);
	}else{
		_color = ofColor(0, 255, 255);
	}
	ofSetColor(_color);
	
	// Draw selection
	ofPolyline line(_corners);
	if(_corners.size() == 4){
		line.setClosed(true);
	}else{
		line.setClosed(false);
	}
	line.draw();
	
	// Draw corners
	for(auto i = 0; i < _corners.size(); ++i){
		ofDrawCircle(_corners[i].x, _corners[i].y, 5);
	}
	ofPopStyle();
	
	// Draw projection so we can see the corners to select
	Application::instance()->projection->draw();

	string textToDraw = "Calibrate mode";
	
	if(_corners.size() < 4){
		string cornerStr;
		switch(_corners.size()){
			case 0:
				cornerStr = "TOP LEFT";
				break;
			case 1:
				cornerStr = "TOP RIGHT";
				break;
			case 2:
				cornerStr = "BOTTOM RIGHT";
				break;
			case 3:
				cornerStr = "BOTTOM LEFT";
				break;
			default:
				break;
		}
		textToDraw += "\nSelect " + cornerStr + " corner";
	}else{
		textToDraw += "\nHit ENTER to confirm";
	}
	
	ofDrawBitmapString(textToDraw, 10, 20);
}

void ModeCalibrate::keyPressed(int key){
	if(key == OF_KEY_ESC){
		_corners.clear();
		Application::instance()->setMode(Mode::DEFAULT);
	}else if(key == OF_KEY_BACKSPACE){
		// Clear last point
		_corners.pop_back();
		highlightCorner();
	}else if(key == OF_KEY_RETURN){
		// Confirm selection if all points are set
		if(_corners.size() == 4){
			Application::instance()->tracker->setTrackArea(_corners);
			_corners.clear();
			Application::instance()->setMode(Mode::DEFAULT);
		}
	}
}

void ModeCalibrate::mousePressed(int x, int y, int button){
	if(button == OF_MOUSE_BUTTON_1 && _corners.size() < 4){
		ofPoint corner;
		corner.x = x;
		corner.y = y;
		_corners.push_back(corner);
		highlightCorner();
	}
}

void ModeCalibrate::highlightCorner(){
	switch(_corners.size()){
		case 0:
			Application::instance()->projection->highlightCorner(Projection::TOP_LEFT);
			break;
		case 1:
			Application::instance()->projection->highlightCorner(Projection::TOP_RIGHT);
			break;
		case 2:
			Application::instance()->projection->highlightCorner(Projection::BOTTOM_RIGHT);
			break;
		case 3:
			Application::instance()->projection->highlightCorner(Projection::BOTTOM_LEFT);
			break;
		default:
			Application::instance()->projection->highlightCorner(Projection::NONE);
			break;
	}
}

} // namespace ytr
