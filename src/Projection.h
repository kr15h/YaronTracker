#pragma once

#include "ofMain.h"
#include "Library.h"

namespace ytr {

class Projection{
public:
	static shared_ptr<Projection> create();

	void update();
	void draw();
	
private:
	Projection();
};

} // namespace ytr
