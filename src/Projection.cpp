#include "Projection.h"

namespace ytr {

shared_ptr<Projection> Projection::create(){
	return shared_ptr<Projection>(new Projection());
}

Projection::Projection(){
	
}

void Projection::update(){
	// Do some swarm math
}

void Projection::draw(){
	// TODO: draw swarm
}

} // namespace ytr
