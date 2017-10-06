#include "CameraPi.h"

namespace ytr{

CameraPi::CameraPi(){
	// Setup camera: width, height, color
    _cam.setup(
			   ofToInt(Settings::instance()->xml.getValue("camera/width")),
			   ofToInt(Settings::instance()->xml.getValue("camera/width")),
			   false);
    _pixels.allocate(_cam.width, _cam.height);
}

void CameraPi::update(){
	// Raspberry Pi camera does not need update.
}

void CameraPi::draw(){
	_cam.draw(0, 0);
}

cv::Mat & CameraPi::getFrame(){
	return _cam.grab();
}

bool CameraPi::isFrameNew(){
	return _cam.isFrameNew();
}

int CameraPi::getWidth(){
	return _cam.getWidth();
}

int CameraPi::getHeight(){
	return _cam.getHeight();
}

} // namespace ytr
