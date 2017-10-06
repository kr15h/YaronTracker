#include "CameraPi.h"

namespace ytr{

CameraPi::CameraPi(){
	int w = ofToInt(Settings::instance()->xml.getValue("camera/width"));
	int h = ofToInt(Settings::instance()->xml.getValue("camera/height"));
	
	cout << "camera width: " << w << endl;
	cout << "camera height: " << h << endl;
	
	// Setup camera: width, height, color
    _cam.setup(w, h, false);
}

void CameraPi::update(){
	// Raspberry Pi camera does not need update.
}

void CameraPi::draw(){
	// ofxCvPiCam does not have draw()
}

cv::Mat CameraPi::getFrame(){
	return _cam.grab();
}

bool CameraPi::isFrameNew(){
	return _cam.isFrameNew();
}

int CameraPi::getWidth(){
	return _cam.width;
}

int CameraPi::getHeight(){
	return _cam.height;
}

} // namespace ytr
