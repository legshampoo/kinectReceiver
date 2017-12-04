#pragma once

#include "draggableImage.h"
#include "ofMain.h"
#include "ofxOsc.h"
#include "pbNetwork.h"
#include "ofxXmlSettings.h"
#include "ofxGui.h"
#include "dashboard.h"
#include "ofxOpenCv.h"
#include "cvPipe.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    //utils
    void openConnections();
    void saveSettings();
    void loadSettings();
    void loadGui();

    string HOST = "localhost";
    int PORT = 12345;

    //tcp
    int imageWidth;
    int imageHeight;
    int imageBytesSize;

    vector<pbNetworkReceiver *> imageReceiver;

    int frameId_1;
    int frameId_2;
    vector<int> frameId;

    int port_1 = 5901;
    int port_2 = 5902;

    vector<int> ports;


    int packetSize = 1024;

    float receiveLastTime_1;
    float receiveLastTime_2;
    vector<float> receiveLastTime;

    int receiveCount_1;
    int receiveCount_2;
    vector<int> receiveCount;

    float receiveFPS_1;
    float receiveFPS_2;
    vector<int> receiveFPS;

    vector<ofImage> image;
    vector<draggableImage> dragImage;

    ofxPanel gui;
    ofxButton saveSettingsBtn;
    ofxButton loadSettingsBtn;
    ofxToggle showOverlays;

    dashboard dash;

    ofxCvGrayscaleImage grayMat;

    ofImage zone;

    cvPipe cvpipe;
};










