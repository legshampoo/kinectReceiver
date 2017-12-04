#include"ofMain.h"
#include "draggableImage.h"

draggableImage::draggableImage()
{

}


void draggableImage::setup(int _id, int w, int h){
    cout << "Set up draggable image" << endl;

    id = _id;
    width = w;
    height = h;
    image.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    image.setColor(defaultColor);

    cout << "Draggable image id: " << id << endl;


    anchorPoint.set(id * width, 400);

}

void draggableImage::update(unsigned char * data, int imgWidth, int imgHeight, ofImageType type){

    int length = strlen((char*)data);
    if(length > 0){
        hasImage = true;
        image.setFromPixels(data, imgWidth, imgHeight, type);
    }else{
        hasImage = false;
    }
}

void draggableImage::draw(){
    ofSetColor(255, 255, 255);
    image.draw(anchorPoint.x, anchorPoint.y);

    if(*showOverlays){
        ofSetColor(anchorPointColor);
        ofNoFill();
        ofSetLineWidth(1);
        ofDrawCircle(anchorPoint.x, anchorPoint.y, anchorRadius);

        ofSetColor(255, 255, 255);
        ofDrawBitmapString(id + " Received frame id = " + ofToString( frameId ), id * width, 10);
        ofDrawBitmapString(id + " Receiving FPS = " + ofToString( receiveFPS, 1), id * width, 40);

    }
}

void draggableImage::handleMousePressed(int x, int y){
    float dist = ofDist(x, y, anchorPoint.x, anchorPoint.y);
    if(dist <= anchorRadius){
        mouseDown = true;
        cout << "ID: " << id << " detected mouse at: " << x << ", " << y << endl;
    }
}

void draggableImage::handleMouseDragged(int x, int y){
    if(mouseDown){
        updateImagePos(x, y);
    }
}

void draggableImage::handleMouseReleased(){
    mouseDown = false;
//    cout << mouseDown << endl;
}

void draggableImage::updateImagePos(int x, int y){
    anchorPoint.set(x, y);
}

