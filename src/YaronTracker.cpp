#include "YaronTracker.h"

namespace ytr{

shared_ptr<YaronTracker> YaronTracker::_instance = 0;

shared_ptr<YaronTracker> YaronTracker::instance(){
	if(_instance == 0){
		_instance = shared_ptr<YaronTracker>(new YaronTracker());
	}
	return _instance;
}

YaronTracker::YaronTracker(){
	cout << "YaronTracker Init" << endl;
	
	_cameraDimensions.width = 800;
	_cameraDimensions.height = 600;
}

void YaronTracker::setup(){
	vector<ofVideoDevice> devices = _camera.listDevices();

    for(int i = 0; i < devices.size(); i = i + 1){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

	_camera.setDeviceID(0);
    _camera.setDesiredFrameRate(60);
    _camera.initGrabber(_cameraDimensions.width, _cameraDimensions.height);
    _cameraTexture.allocate(_cameraDimensions.width, _cameraDimensions.height, OF_PIXELS_RGB);
}

void YaronTracker::update(){
    _camera.update();
    if(_camera.isFrameNew()){
        _cameraTexture.loadData(_camera.getPixels());
    }
}

void YaronTracker::draw(){
	_camera.draw(0, 0);
}

} // namespace ytr
