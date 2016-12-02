#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
    //ofAppGlutWindow window;
    //ofSetupOpenGL(&window, 1280, 480, OF_WINDOW);
    ofSetupOpenGL(1024*2, 768, OF_WINDOW);
	ofRunApp(new testApp());
}
