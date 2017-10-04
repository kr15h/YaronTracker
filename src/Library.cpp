#include "Library.h"

namespace ytr {

shared_ptr<Library> Library::_instance = 0;

shared_ptr<Library> Library::instance(){
	if(_instance == 0){
		_instance = shared_ptr<Library>(new Library);
	}
	return _instance;
}

Library::Library(){
	images.arrow.load("arrow.png");
}

} // namespace ytr
