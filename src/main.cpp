#include "ofMain.h"
#include "ofApp.h"

int main(){
	#ifdef TARGET_RASPBERY_PI
		ofSetupOpenGL(1280, 640, OF_FULLSCREEN);
	#else
		ofSetupOpenGL(1280, 640, OF_WINDOW);
	#endif
	ofRunApp(new ofApp);
}
