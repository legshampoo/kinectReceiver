#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "ofMain.h"

class dashboard
{
public:
    dashboard();

    void setup(int w, int h);
    void update();
    void draw();
    void drawKinectFeedBoundingRect();
    void drawCvBoundingRect();

    int zoneWidth = 320 * 2;
    int zoneHeight = 240 * 2;

    //rectangle
    ofPoint zoneP1 = ofPoint(100, 200);
    ofPoint zoneP2 = ofPoint(zoneP1.x + zoneWidth, zoneP1.y);
    ofPoint zoneP3 = ofPoint(zoneP1.x + zoneWidth, zoneHeight);
    ofPoint zoneP4 = ofPoint(zoneP1.x, zoneHeight);

    int margin = 200;
    ofPoint cvBoundsOrigin = ofPoint(zoneP1.x + zoneWidth + margin, 200);
    int cvBoundsWidth = zoneWidth;
    int cvBoundsHeight = zoneHeight;
};

#endif // DASHBOARD_H
