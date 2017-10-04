#include "Settings.h"

namespace ytr {

shared_ptr<Settings> Settings::_instance = 0;

shared_ptr<Settings> Settings::instance(){
	if(_instance == 0){
		_instance = shared_ptr<Settings>(new Settings);
	}
	return _instance;
}

Settings::Settings(){
	bool loaded = xml.load("settings.xml");
	cout << "Loading settings: " << loaded << endl;
	xml.setTo("settings");
}

bool Settings::save(){
	bool saved = xml.save("settings.xml");
	cout << "Saving settings: " << saved << endl;
	return saved;
}

} // namespace ytr
