#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
  void exit();
	
	ofVideoGrabber cam;
  
  bool isSomethingDetected = false;
  
  // Continous background getting updated.
	ofxCv::RunningBackground background;
  
  // Background subtracted image.
	ofImage thresholded;
  
  // Contour Finder that detects a hand.
  ofxCv::ContourFinder contourFinder;
  
  ofxPanel gui;
  ofParameter<bool> resetBackground;
  
  ofxGuiGroup bgGroup;
  ofParameter<float> learningTime, thresholdValue;

  ofxGuiGroup contourFinderGroup;
  ofParameter<float> minArea, maxArea, threshold;
};
