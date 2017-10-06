#pragma once

#include "ofMain.h"

#include "Camera.h"
#ifdef TARGET_RASPBERRY_PI
	#include "CameraPi.h"
#else
	#include "CameraAll.h"
#endif

namespace ytr {

class CameraFactory{
public:
	static shared_ptr<Camera> create();
};

} // namespace ytr
