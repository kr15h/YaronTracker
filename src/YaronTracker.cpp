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
}

void YaronTracker::update(){
    Camera::instance()->update();
}

void YaronTracker::draw(){
	Camera::instance()->draw();
}

} // namespace ytr
