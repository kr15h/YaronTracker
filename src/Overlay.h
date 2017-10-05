#pragma once

#include "ofMain.h"
#include "Library.h"

namespace ytr {

class Overlay{
public:
	static shared_ptr<Overlay> create();
	
	enum Corner{
		NONE,
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_RIGHT,
		BOTTOM_LEFT
	};
	
	void draw();
	void showCorner(Corner $corner);

private:
	Overlay();
	
	Corner _cornerToShow;
};

} // namespace ytr
