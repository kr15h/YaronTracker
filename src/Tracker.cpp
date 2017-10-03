#include "Tracker.h"

namespace ytr {

shared_ptr<Tracker> Tracker::create(){
	return shared_ptr<Tracker>(new Tracker());
}

Tracker::Tracker(){
	
}

void Tracker::update(){

}

void Tracker::draw(){

}

} // namespace ytr
