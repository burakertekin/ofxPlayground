#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);

    bool bLearnBackground;
    ofVideoGrabber vidGrabber;
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImage, grayBg, grayDiff;
    ofxCvContourFinder contourFinder;

    int m_width, m_height;

    ofImage edge ;
    ofxCvGrayscaleImage edgecanny ;

    ofxPanel gui;
    ofParameter<int> cannyParam1, cannyParam2, numcontours ;

    vector < ofPoint > facePoints;
    vector < ofPoint > drawnPoints;

    ofPolyline line;

    vector < ofPolyline > allLines;

    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

};
