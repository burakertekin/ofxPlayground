#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "Clone.h"
#include "ofxFaceTracker.h"
#include "ofxFaceTrackerThreaded.h"

#include <limits>

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void dragEvent(ofDragInfo dragInfo);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
	void loadPoints(string filename);
	void loadFace(string filename);
	
	void keyPressed(int key);
	void keyReleased(int key);

    void drawHighlightString(string text, int x, int y);

	ofxFaceTrackerThreaded camTracker;
	ofVideoGrabber cam;
	
	ofxFaceTracker srcTracker;
	ofImage src;
    //vector<ofVec2f> srcPoints;
    vector<glm::vec2> srcPoints;
	vector<int> selectedPoints;
	vector<int> dragPoints;
	vector<ofVec2f> dragPointsToMouse;
	
	bool selectArea;
	ofVec2f selectAreaStart;
	
	bool cloneReady;
	Clone clone;
	ofFbo srcFbo, maskFbo;
	
	static const int lines [];
	
	long mousePressedTime;
};
