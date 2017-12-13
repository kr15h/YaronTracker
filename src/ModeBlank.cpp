#include "ModeBlank.h"

namespace ytr {

shared_ptr<Mode> ModeBlank::_instance = 0;

shared_ptr<Mode> ModeBlank::instance(){
	if(_instance == 0){
		_instance = shared_ptr<ModeBlank>(new ModeBlank);
	}
	return _instance;
}

ModeBlank::ModeBlank(){
	cout << "ModeBlank" << endl;
}

} // namespace ytr
