/*
 *  ofxHomographyHelper.cpp
 *  Created by Elliot Woods on 26/11/2010.
 *  Ported back to openFrameworks by Krisjanis Rijnieks 7/10/2017
 *
 *  Ported to cinder 12/12/2011 by Charlie Whitney
 *
 *  Based entirely on arturo castro's homography implementation
 *  Created 08/01/2010, arturo castro
 *
 *	http://www.openframeworks.cc/forum/viewtopic.php?f=9&t=3121
 */

#pragma once

#include "ofMain.h"

class ofxHomographyHelper {
public:
	static void	gaussian_elimination(float *input, int n);
	static void	findHomography(ofVec2f src[4], ofVec2f dst[4], float homography[16]);
	static ofMatrix4x4 findHomography(float src[4][2], float dst[4][2]);
};

