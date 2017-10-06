#include "CameraAll.h"

namespace ytr{

CameraAll::CameraAll(){
	vector<ofVideoDevice> devices = _videoGrabber.listDevices();

    for(int i = 0; i < devices.size(); i = i + 1){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

	// TODO: Get device id from settings
	_videoGrabber.setDeviceID(0);
    _videoGrabber.setDesiredFrameRate(60);
	_videoGrabber.setPixelFormat(OF_PIXELS_RGB);
    _videoGrabber.initGrabber(
		ofToInt(Settings::instance()->xml.getValue("camera/width")),
		ofToInt(Settings::instance()->xml.getValue("camera/height"))
    );
}

void CameraAll::update(){
	_videoGrabber.update();
}

void CameraAll::draw(){
	_videoGrabber.draw(0, 0);
}

cv::Mat CameraAll::getFrame(){
	ofxCv::copyGray(_videoGrabber.getPixels(), _grayPixels);
	_frame = ofxCv::toCv(_grayPixels);
	return _frame;
}

bool CameraAll::isFrameNew(){
	return _videoGrabber.isFrameNew();
}

int CameraAll::getWidth(){
	return _videoGrabber.getWidth();
}

int CameraAll::getHeight(){
	return _videoGrabber.getHeight();
}

} // namespace ytr
