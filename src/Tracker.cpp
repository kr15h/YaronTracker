#include "Tracker.h"

namespace ytr {

shared_ptr<Tracker> Tracker::create(){
	return shared_ptr<Tracker>(new Tracker);
}

Tracker::Tracker(){
	int w = ofToInt(Settings::instance()->xml.getValue("camera/width"));
	int h = ofToInt(Settings::instance()->xml.getValue("camera/height"));

	cout << "camera width: " << w << endl;
	cout << "camera height: " << h << endl;
	
	#ifdef TARGET_RASPBERRY_PI
		cam.setup(w, h, false);
	#else
		vector<ofVideoDevice> camList = cam.listDevices();
		bool camFound = false;
		for(auto i = 0; i < camList.size(); ++i){
			cout << "Device Name: " << camList[i].deviceName << endl;
			if(ofIsStringInString(camList[i].deviceName, "Logitech")){
				cout << "Found Logitech camera: " << camList[i].deviceName << endl;
				cam.setDeviceID(i);
				camFound = true;
				break;
			}
		}
	
		if(!camFound){
			cout << "Logitech camera not found, using whatever is at index 0" << endl;
			cam.setDeviceID(0);
		}

		cam.setDesiredFrameRate(60);
		cam.setPixelFormat(OF_PIXELS_RGB);
		cam.initGrabber(w, h);
	#endif

	// Set the corners for cropping the tracking area.
	_areaSrcPoints.resize(4);
	_areaSrcPoints[0].x = ofToFloat(Settings::instance()->xml.getValue("projection/tl/x"));
	_areaSrcPoints[0].y = ofToFloat(Settings::instance()->xml.getValue("projection/tl/y"));
	_areaSrcPoints[1].x = ofToFloat(Settings::instance()->xml.getValue("projection/tr/x"));
	_areaSrcPoints[1].y = ofToFloat(Settings::instance()->xml.getValue("projection/tr/y"));
	_areaSrcPoints[2].x = ofToFloat(Settings::instance()->xml.getValue("projection/br/x"));
	_areaSrcPoints[2].y = ofToFloat(Settings::instance()->xml.getValue("projection/br/y"));
	_areaSrcPoints[3].x = ofToFloat(Settings::instance()->xml.getValue("projection/bl/x"));
	_areaSrcPoints[3].y = ofToFloat(Settings::instance()->xml.getValue("projection/bl/y"));
	
	setDestArea();
	
	_minAreaRadius = ofToFloat(Settings::instance()->xml.getValue("contourFinder/minAreaRadius"));
	_maxAreaRadius = ofToFloat(Settings::instance()->xml.getValue("contourFinder/maxAreaRadius"));
	
	// Set contour finder settings
	// TODO: Set threshold from settings and allow realtime adjustment.
	_contourFinder.setThreshold(Settings::instance()->threshold);
	_contourFinder.setMinAreaRadius(Settings::instance()->minAreaRadius);
	_contourFinder.setMaxAreaRadius(Settings::instance()->maxAreaRadius);
	_contourFinder.setSortBySize(true);
}

void Tracker::update(){

	// Update the threshold of the contour tracker on every frame
	_contourFinder.setThreshold(Settings::instance()->threshold);
	_contourFinder.setMinAreaRadius(Settings::instance()->minAreaRadius);
	_contourFinder.setMaxAreaRadius(Settings::instance()->maxAreaRadius);

	#ifndef TARGET_RASPBERRY_PI
		cam.update();
	#endif

	if(cam.isFrameNew()){
		
		#ifdef TARGET_RASPBERRY_PI

			_frame = cam.grab();
		
			if(_frame.empty()){
				return;
			}

			_contourFinder.findContours(_frame);
		
		#else
		
			ofxCv::copyGray(cam.getPixels(), _frame);
			_contourFinder.findContours(_frame);

		#endif
		
		// We do this in case the window size changed during app runtime operation.
		setDestArea();
		
		if(_contourFinder.size()){
			
			// Use ofxHomographyHelper to map the point
			// from camera to warped image dimensions.
			float src[4][2];
			float dst[4][2];

			src[0][0] = _areaSrcPoints[0].x;
			src[0][1] = _areaSrcPoints[0].y;
			src[1][0] = _areaSrcPoints[1].x;
			src[1][1] = _areaSrcPoints[1].y;
			src[2][0] = _areaSrcPoints[2].x;
			src[2][1] = _areaSrcPoints[2].y;
			src[3][0] = _areaSrcPoints[3].x;
			src[3][1] = _areaSrcPoints[3].y;
			
			dst[0][0] = _areaDstPoints[0].x;
			dst[0][1] = _areaDstPoints[0].y;
			dst[1][0] = _areaDstPoints[1].x;
			dst[1][1] = _areaDstPoints[1].y;
			dst[2][0] = _areaDstPoints[2].x;
			dst[2][1] = _areaDstPoints[2].y;
			dst[3][0] = _areaDstPoints[3].x;
			dst[3][1] = _areaDstPoints[3].y;
			
			ofMatrix4x4 homography = ofxHomographyHelper::findHomography(src, dst);
			
			ofVec3f srcPos;
			srcPos.x = _contourFinder.getCenter(0).x;
			srcPos.y = _contourFinder.getCenter(0).y;
			ofVec3f dstPos = homography * srcPos;
			
			_srcPosition.x = srcPos.x;
			_srcPosition.y = srcPos.y;
			
			_position.x = dstPos.x;
			_position.y = dstPos.y;
		}
	}
}

void Tracker::draw(){
	ofxCv::drawMat(_frame, 0, 0, getWidth(), getHeight());
	_contourFinder.draw();
	
	// Draw the quad where tracking action happens
	ofPushStyle();
	ofSetColor(255, 255, 0);
	ofPolyline line;
	line.addVertices(_areaSrcPoints);
	line.setClosed(true);
	line.draw();
	ofSetColor(0, 255, 255);
	ofDrawCircle(_srcPosition.x, _srcPosition.y, 10);
	ofPopStyle();
	
	// Draw the min and max size for contour finder
	ofPushStyle();
	ofNoFill();
	ofSetColor(255, 0, 0);
	ofDrawCircle(ofGetWidth() - Settings::instance()->maxAreaRadius - 10, Settings::instance()->maxAreaRadius + 10, Settings::instance()->minAreaRadius);
	ofSetColor(0, 255, 255);
	ofDrawCircle(ofGetWidth() - Settings::instance()->maxAreaRadius - 10, Settings::instance()->maxAreaRadius + 10, Settings::instance()->maxAreaRadius);
	ofPopStyle();
}

void Tracker::setTrackArea(vector<ofPoint> & $corners){
	_areaSrcPoints = $corners;
	
	Settings::instance()->xml.setValue("projection/tl/x", ofToString(_areaSrcPoints[0].x, 0));
	Settings::instance()->xml.setValue("projection/tl/y", ofToString(_areaSrcPoints[0].y, 0));
	Settings::instance()->xml.setValue("projection/tr/x", ofToString(_areaSrcPoints[1].x, 0));
	Settings::instance()->xml.setValue("projection/tr/y", ofToString(_areaSrcPoints[1].y, 0));
	Settings::instance()->xml.setValue("projection/br/x", ofToString(_areaSrcPoints[2].x, 0));
	Settings::instance()->xml.setValue("projection/br/y", ofToString(_areaSrcPoints[2].y, 0));
	Settings::instance()->xml.setValue("projection/bl/x", ofToString(_areaSrcPoints[3].x, 0));
	Settings::instance()->xml.setValue("projection/bl/y", ofToString(_areaSrcPoints[3].y, 0));
}

void Tracker::setDestArea(){

	// We use the window size as the destination rectangle.
	_areaDstPoints.resize(4);
	_areaDstPoints[0].x = 0;
	_areaDstPoints[0].y = 0;
	_areaDstPoints[1].x = ofGetWidth();
	_areaDstPoints[1].y = 0;
	_areaDstPoints[2].x = ofGetWidth();
	_areaDstPoints[2].y = ofGetHeight();
	_areaDstPoints[3].x = 0;
	_areaDstPoints[3].y = ofGetHeight();
}

ofVec2f Tracker::getPosition(){
	return _position;
}

int Tracker::getWidth(){
	#ifdef TARGET_RASPBERRY_PI
		return cam.width;
	#else
		return cam.getWidth();
	#endif
}

int Tracker::getHeight(){
	#ifdef TARGET_RASPBERRY_PI
		return cam.height;
	#else
		return cam.getHeight();
	#endif
}

cv::Mat & Tracker::getFrame(){
	return _frame;
}

} // namespace ytr
