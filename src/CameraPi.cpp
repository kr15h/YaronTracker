#include "CameraPi.h"

namespace ytr{

CameraPi::CameraPi(){
	int w = ofToInt(Settings::instance()->xml.getValue("camera/width"));
	int h = ofToInt(Settings::instance()->xml.getValue("camera/height"));
	
	cout << "camera width: " << w << endl;
	cout << "camera height: " << h << endl;
	
	// Setup camera: width, height, color
	cout << "Attempting to setup camera" << endl;
    _cam.setup(w, h, false);
    cout << "Camera setup successful" << endl;
}

void CameraPi::update(){
	// Raspberry Pi camera does not need update.
}

void CameraPi::draw(){
	ofxCv::drawMat(_cam.grab(), 0, 0);
}

cv::Mat CameraPi::getFrame(){
	return _cam.grab();
}

bool CameraPi::isFrameNew(){
	return true;
	//return _cam.isFrameNew();
}

int CameraPi::getWidth(){
	return _cam.width;
}

int CameraPi::getHeight(){
	return _cam.height;
}

} // namespace ytr
