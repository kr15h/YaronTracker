#include "Camera.h"

namespace ytr{

shared_ptr<Camera> Camera::create(){
	return shared_ptr<Camera>(new Camera());
}

Camera::Camera(){
	// TODO: get values from settings
	_dimensions.width = 800;
	_dimensions.height = 600;
	
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
    _videoGrabber.initGrabber(_dimensions.width, _dimensions.height);
}

void Camera::update(){
	_videoGrabber.update();
}

void Camera::draw(){
	_videoGrabber.draw(0, 0);
}

ofTexture & Camera::getTexture(){
	return _videoGrabber.getTexture();
}

} // namespace ytr
