#include "cvPipe.h"

cvPipe::cvPipe()
{

}

void cvPipe::setup(int w, int h, dashboard d){
    cout << "Setting up CV pipeline" << endl;

    imgWidth = w;
    imgHeight = h;
    grabOrigin.set(d.zoneP1.x, d.zoneP1.y);

    drawOrigin = d.cvBoundsOrigin;

    colorMat.allocate(imgWidth, imgHeight);
    grayMat.allocate(imgWidth, imgHeight);

    grayBg.allocate(imgWidth, imgHeight);
    grayDiff.allocate(imgWidth, imgHeight);



    setupGui();

    learnBackground = false;

}

void cvPipe::update(){
    screengrab.grabScreen(grabOrigin.x, grabOrigin.y, imgWidth, imgHeight);
    colorMat.setFromPixels(screengrab);
    grayMat.setFromColorImage(colorMat);

    for(int k = 0; k < erode; k++){
        grayMat.erode();
    }

    grayMat.blurGaussian(blur);

    grayMat.threshold(threshold, false);


    for(int k = 0; k < dilate; k++){
        grayMat.dilate();
    }


    if(learnBackground){
        grayBg = grayMat;
        learnBackground = false;
    }

    grayDiff.absDiff(grayBg, grayMat);

    contourFinder.findContours(grayMat, minBlobSize, maxBlobSize, maxNumBlobs, findHoles, useApproximation);

    blobs = contourFinder.blobs;
    numBlobsDetected = contourFinder.blobs.size();

    for(int i = 0; i < blobs.size(); i++){
        ofxCvBlob b = blobs[i];
        ofPoint centroid;
        centroid.set(b.centroid.x, b.centroid.y);
    }

}

void cvPipe::draw(){
    grayMat.draw(drawOrigin.x, drawOrigin.y);

    contourFinder.draw(drawOrigin.x, drawOrigin.y);
    gui.draw();
}

void cvPipe::setupGui(){
    gui.setup();

    gui.add(erode.setup("Erode", 2, 0, 10));
    gui.add(blur.setup("Blur", 5, 0, 25));
    gui.add(threshold.setup("Threshold", 254, 0, 255));
    gui.add(dilate.setup("Dilate", 4, 0, 10));
    gui.add(minBlobSize.setup("Min Blob Size", 0, 0, 500));
    gui.add(maxBlobSize.setup("Max Blob Size", 3000, 0, maxSize));
    gui.add(findHoles.setup("Find Holes", false));
    gui.add(useApproximation.setup("Use Approx.", false));
}
