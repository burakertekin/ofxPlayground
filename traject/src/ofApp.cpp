#include "ofApp.h"

using namespace ofxCv;
//using namespace cv;

int paintPoints = 0 ;
int blobi = 0 ;
int blobj = 0 ;
ofPolyline newline;

int step = 0 ;
int breakpoints = 0 ;

bool start = false;

//--------------------------------------------------------------
void ofApp::setup(){
    bLearnBackground = false;

    m_width = 800;
    m_height = 600;

    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(m_width, m_height);

    colorImg.allocate(m_width, m_height);
    grayImage.allocate(m_width, m_height);
    grayBg.allocate(m_width, m_height);
    grayDiff.allocate(m_width, m_height);

    gui.setup();
    gui.add(cannyParam1.set("cannyParam1", 400, 0, 1024));
    gui.add(cannyParam2.set("cannyParam2", 600, 0, 1024));
    gui.add(numcontours.set("numcontours", 20, 0, 200));
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    //do we have a new frame?
    if(vidGrabber.isFrameNew())
    {
        colorImg.setFromPixels(vidGrabber.getPixels());
        grayImage = colorImg;//convert our color image to a grayscale image
        if(bLearnBackground == true)
        {
            grayBg = grayImage;//update the bground image
            bLearnBackground = false;
        }
        /*
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(30);
        contourFinder.findContours(grayDiff, 5, (340*240)/4, false, true);
        */

        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(150);

        //Canny edge detection
        Canny(grayDiff, edge, cannyParam1*2, cannyParam2*2, 3);
        edge.update();
        edgecanny = edge ; // convert canny image into grayscale image

        edgecanny.dilate() ;
        edgecanny.erode() ;
        contourFinder.findContours(edgecanny, 5, (m_width*m_height), numcontours, true, true);

        if(start == true)
        {
            //Code to add randomness to lines
             for (int i = 0 ; i < contourFinder.nBlobs ; i++)
             {
                 for (auto &vert : allLines[i].getVertices())
                 {
                    vert.x += ofRandom(-5,5);
                    vert.y += ofRandom(-5,5);
                 }
             }

        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    /*
    ofSetHexColor(0xffffff);
    colorImg.draw(0,0,m_width, m_height);
    grayDiff.draw(0,m_height,m_width,m_height);
    ofDrawRectangle(m_width,0,m_width,m_height);
    contourFinder.draw(m_width,0,m_width,m_height);
    ofColor c(255,255,255);
    for(int i = 0; i < contourFinder.nBlobs; ++i)
    {
        ofRectangle r = contourFinder.blobs.at(i).boundingRect;
        r.x += m_width;
        r.y += m_height;
        c.setHsb(i*64,255,255);
        ofSetColor(c);
        ofDrawRectangle(r);
    }
    */

    if(start==false) {
        ofSetHexColor(0xffffff);

        //colorImg.draw(0, 0, 320, 240);
        //grayDiff.draw(0, 240, 320, 240);
        //ofDrawRectangle(320, 0, 320, 240);

        edgecanny.draw(0,0,m_width,m_height);
        contourFinder.draw(0,0,m_width,m_height);

        gui.draw();
    }
    else {
        ofBackground(0);

        ofEnableAlphaBlending();
        ofSetColor(200,200,200, 10);
        ofFill() ;

        //Draw Contours
        ofSetLineWidth(1) ;

        for (int z = 0 ; z < allLines.size() ; z ++) {
            allLines[z].draw() ;
        }

        for (int i = 0 ; i < contourFinder.nBlobs ; i++) {
            if(blobj < contourFinder.blobs.at(i).nPts) {
                float x = contourFinder.blobs.at(i).pts[blobj].x ;
                float y = contourFinder.blobs.at(i).pts[blobj].y ;
                ofPoint newpoint ;
                newpoint.set(x,y) ;

                allLines[i].addVertex(newpoint) ;

                drawnPoints.push_back(newpoint) ;

                if(breakpoints == 4 ) {
                    for (auto point : drawnPoints){
                        float dist = (newpoint - point).length();
                        if (dist < 30){
                            ofPolyline lineTemp;
                            lineTemp.addVertex(newpoint) ;
                            lineTemp.addVertex(point) ;
                            allLines.push_back(lineTemp) ;
                        }
                    }
                    breakpoints = 0 ;

                }
                else {
                    breakpoints++ ;
                }

            }
        }

        blobj++ ;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //bLearnBackground = true;

    if(key == 'b') { // Background substraction when b is pressed
            bLearnBackground = true;
        }

        if (key == ' ') { // Take the image when space is pressed
            start = true ;

            //Count contours
            for(int i = 0; i < contourFinder.nBlobs; i++) {
                if(contourFinder.blobs.size() != 0) {
                    for (int j = 0; j < contourFinder.blobs.at(i).nPts; j++) {
                        float x = contourFinder.blobs.at(i).pts[j].x ;
                        float y = contourFinder.blobs.at(i).pts[j].y ;
                        facePoints.push_back(ofPoint(x,y));
                    }
                }
            }
            cout << facePoints.size() ; // Just a sanity check

            ofBackground(255,255,255);

            for (int z = 0 ; z < contourFinder.nBlobs; z++) {
                allLines.push_back(newline) ;
            }

            ofSetFrameRate(60); // increase frame rate
        }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
