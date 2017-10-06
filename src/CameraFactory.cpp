#include "CameraFactory.h"

namespace ytr {

shared_ptr<Camera> CameraFactory::create(){
#ifdef TARGET_RASPBERRY_PI
	return shared_ptr<Camera>(new CameraPi);
#else
	return shared_ptr<CameraAll>(new CameraAll);
#endif
}

} // namespace ytr
