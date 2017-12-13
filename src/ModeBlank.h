#pragma once

#include "ofMain.h"
#include "Mode.h"
#include "Application.h"
#include "Projection.h"
#include "Settings.h"

namespace ytr {

class Mode;

class ModeBlank : public Mode{
public:
	static shared_ptr<Mode> instance();
	
private:
	static shared_ptr<Mode> _instance;
	ModeBlank();
};

} // namespace ytr
