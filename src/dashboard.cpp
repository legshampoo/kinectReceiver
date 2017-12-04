#include "dashboard.h"

dashboard::dashboard()
{

}

void dashboard::setup(int w, int h){
    cout << "Setting up dashboard" << endl;
}

void dashboard::update(){

}

void dashboard::draw(){
    drawKinectFeedBoundingRect();
    drawCvBoundingRect();
}

void dashboard::drawKinectFeedBoundingRect(){
    ofSetColor(200, 50, 200);
    ofNoFill();
    ofSetLineWidth(1);
    ofRectangle zoneRect;
    zoneRect.x = zoneP1.x;
    zoneRect.y = zoneP1.y;
    zoneRect.width = zoneWidth;
    zoneRect.height = zoneHeight;
    ofDrawRectangle(zoneRect);

}

void dashboard::drawCvBoundingRect(){
    ofSetColor(200, 50, 200);
    ofNoFill();
    ofSetLineWidth(1);
    ofRectangle cvBoundsRect;
    cvBoundsRect.x = cvBoundsOrigin.x;
    cvBoundsRect.y = cvBoundsOrigin.y;
    cvBoundsRect.width = cvBoundsWidth;
    cvBoundsRect.height = cvBoundsHeight;

    ofDrawRectangle(cvBoundsRect);
}
