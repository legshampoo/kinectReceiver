#ifndef DRAGGABLEIMAGE_H
#define DRAGGABLEIMAGE_H

#include "ofMain.h"
#include "ofxGui.h"

class draggableImage {
public:
    int id;
    int width;
    int height;
    int anchorRadius = 20;
    void setup(int _id, int w, int h);
    void update(unsigned char * data, int imgWidth, int imgHeight, ofImageType type);
    void draw();
    void handleMousePressed(int x, int y);
    void handleMouseReleased();
    void handleMouseDragged(int x, int y);
    void updateImagePos(int x, int y);

    int frameId;
    int receiveCount;
    float receiveLastTime;
    float receiveFPS;

    ofImage image;
    ofColor defaultColor = ofColor(255, 0, 255);
    ofColor anchorPointColor = ofColor(0, 255, 0, 100);
    ofVec2f anchorPoint;

    draggableImage();
    bool mouseDown = false;
    bool hasImage = false;
    ofxToggle *showOverlays = reinterpret_cast<ofxToggle*>(ofGetAppPtr());
};

#endif // DRAGGABLEIMAGE_H
