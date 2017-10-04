#pragma once

#include "ofMain.h"

namespace ytr {

class Projection{
public:
	static shared_ptr<Projection> create();

	void update();
	void draw();
	
	enum Corner{
		NONE,
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_RIGHT,
		BOTTOM_LEFT
	};
	
	void highlightCorner(Corner $corner);
	
private:
	Projection();
	
	Corner _cornerToHighlight;
};

} // namespace ytr
