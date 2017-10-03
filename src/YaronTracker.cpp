#include "YaronTracker.h"

namespace ytr{

shared_ptr<YaronTracker> YaronTracker::create(){
	return shared_ptr<YaronTracker>(new YaronTracker());
}

YaronTracker::YaronTracker(){
	_camera = Camera::create();
	_tracker = Tracker::create();
}

void YaronTracker::update(){
	_camera->update();
	_tracker->update();
}

void YaronTracker::draw(){
	_camera->draw();
	_tracker->update();
}

} // namespace ytr
