#include "Application.h"

namespace ytr{

shared_ptr<Application> Application::create(){
	return shared_ptr<Application>(new Application());
}

Application::Application(){
	_camera = Camera::create();
	_tracker = Tracker::create();
}

void Application::update(){
	_camera->update();
	_tracker->update();
}

void Application::draw(){
	_camera->draw();
	_tracker->update();
}

} // namespace ytr
