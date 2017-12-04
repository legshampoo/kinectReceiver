#ifndef CVPIPE_H
#define CVPIPE_H

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "dashboard.h"
#include "ofxGui.h"

class cvPipe
{
public:
    cvPipe();
    void setup(int w, int h, dashboard d);
    void update();
    void draw();
    void setupGui();

    ofImage screengrab;
    ofVec2f grabOrigin;
    ofxCvColorImage colorMat;
    ofxCvGrayscaleImage grayMat;
    int imgWidth;
    int imgHeight;
    ofVec2f drawOrigin;

    ofxPanel gui;
    ofxIntSlider threshold;
    ofxIntSlider blur;
    ofxIntSlider dilate;
    ofxIntSlider erode;
    ofxIntSlider minBlobSize;
    ofxIntSlider maxBlobSize;
    ofxToggle findHoles;
    ofxToggle useApproximation;

    int maxNumBlobs = 1000;
    int maxSize = 5000;

    ofxCvContourFinder contourFinder;
    ofxCvGrayscaleImage grayBg, grayDiff;
    bool learnBackground;
    vector<ofxCvBlob> blobs;
    int numBlobsDetected;
};

#endif // CVPIPE_H
