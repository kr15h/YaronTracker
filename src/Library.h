#pragma once

#include "ofMain.h"

namespace ytr {

class Library{
public:
	static shared_ptr<Library> instance();
	
	struct {
		ofImage arrow;
	} images;

private:
	static shared_ptr<Library> _instance;
	Library();
};

} // namespace ytr
