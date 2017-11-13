#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	cam.setup(640, 480);
  
  // GUI Setup.
  gui.setup();
  
  bgGroup.setup("Background");
  bgGroup.add(resetBackground.set("Reset Background", false));
  bgGroup.add(learningTime.set("Learning Time", 30, 0, 60));
  bgGroup.add(thresholdValue.set("Threshold Value", 10, 0, 255));
  
  gui.add(&bgGroup);

  contourFinderGroup.setup("Contour Finder");
  
  // Contour finder parameters.
  contourFinderGroup.add(minArea.set("Min area", 10, 1, 100));
  contourFinderGroup.add(maxArea.set("Max area", 200, 1, 500));
  contourFinderGroup.add(threshold.set("Threshold", 128, 0, 255));
  
  gui.add(&contourFinderGroup);
  
  gui.loadFromFile("cameraDetector.xml");
}

void ofApp::update() {
	cam.update();
  
  if(resetBackground) {
      background.reset();
      resetBackground = false;
  }
  
	if(cam.isFrameNew()) {
      // Set running background parameters.
      background.setLearningTime(learningTime);
      background.setThresholdValue(thresholdValue);
      background.update(cam, thresholded);
      thresholded.update();

    
      // Set contour finder parameters.
      contourFinder.setMinAreaRadius(minArea);
      contourFinder.setMaxAreaRadius(maxArea);
      contourFinder.setThreshold(threshold);
    
      // Find contours in the thresholded image.
      contourFinder.findContours(thresholded);
    
      // Get all the contours
      vector <ofPolyline> polylines = contourFinder.getPolylines();
    
      // True if something is detected.
      // False if nothing is detected.
      // Do work based on this value.
      isSomethingDetected = (polylines.size() > 0);
	}
}

void ofApp::draw() {
	cam.draw(0, 0);
  
  if(thresholded.isAllocated()) {
      thresholded.draw(640, 0);
    
      // Draw the contours.
      contourFinder.draw();
  }
    
  gui.draw();
}

void ofApp::exit() {
  gui.saveToFile("cameraDetector.xml");
}
