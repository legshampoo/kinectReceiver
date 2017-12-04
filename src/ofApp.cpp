#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(100, 100, 0);

    cout << "Receiver INIT" << endl;
    cout << system("hostname") << endl;

    //tcp
    imageWidth = 320;
    imageHeight = 240;
    imageBytesSize = imageWidth * imageHeight; //*3

    openConnections();

    dash.setup(imageWidth, imageHeight);

    int screengrabWidth = imageWidth * 2;
    int screengrabHeight = imageHeight * 2;
    cvpipe.setup(screengrabWidth, screengrabHeight, dash);
    loadGui();

    loadSettings();

    grayMat.allocate(dash.zoneWidth, dash.zoneHeight);
}

void ofApp::openConnections(){
    ports.push_back(5500);
    ports.push_back(5501);
    ports.push_back(5502);
    ports.push_back(5503);
    ports.push_back(5504);

    for(int i = 0; i < 5; i++){
        pbNetworkReceiver *r = new pbNetworkReceiver();
        imageReceiver.push_back(r);
        imageReceiver[i]->setup(ports[i], packetSize, true);

        draggableImage dImg;
        dImg.setup(i, imageWidth, imageHeight);
        dImg.frameId = -1;
        dImg.receiveCount = 0;
        dImg.receiveFPS = 0;
        dImg.receiveLastTime = 0;
        dImg.showOverlays = &showOverlays;

        dragImage.push_back(dImg);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    for(int i = 0; i < 5; i++){
        if(imageReceiver[i]->frame() != dragImage[i].frameId){
            dragImage[i].frameId = imageReceiver[i]->frame();

            if(imageReceiver[i]->size() == imageBytesSize){
                unsigned char * data = &imageReceiver[i]->data()[0];
                dragImage[i].update(data, imageWidth, imageHeight, OF_IMAGE_GRAYSCALE);
            }else{
                cout << "ERROR on " << i << endl;
            }

            dragImage[i].receiveCount++;

            float fpsUpdateSec = 1.0;
            float time = ofGetElapsedTimef();

            if(time >= dragImage[i].receiveLastTime + fpsUpdateSec){
                dragImage[i].receiveFPS = dragImage[i].receiveCount / (time - dragImage[i].receiveLastTime);
                dragImage[i].receiveLastTime = time;
                dragImage[i].receiveCount = 0;
            }
        }
    }

    cvpipe.update();
    //zone.grabScreen(dash.zoneP1.x, dash.zoneP1.y, dash.zoneWidth, dash.zoneHeight);
//    zone.allocate(dash.zoneWidth, dash.zoneHeight, OF_PIXELS_GRAY);
//    zone.grabScreen(dash.zoneP1.x, dash.zoneP1.y, 200, 200);
//    grayMat.setFromPixels(zone.getPixels());
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    for(int i = 0; i < 5; i++){
        if(dragImage[i].image.isAllocated() && dragImage[i].hasImage){
            dragImage[i].draw();
        }
    }

    gui.draw();

    cvpipe.draw();

    dash.draw();
}

void ofApp::loadGui(){
    gui.setup();

    saveSettingsBtn.addListener(this, &ofApp::saveSettings);
    gui.add(saveSettingsBtn.setup("Save Settings"));

    loadSettingsBtn.addListener(this, &ofApp::loadSettings);
    gui.add(loadSettingsBtn.setup("Load Settings"));

    gui.add(showOverlays.setup("Show Overlays", true));
}


void ofApp::saveSettings(){
    ofxXmlSettings settings;

    settings.addTag("kinects");
    settings.pushTag("kinects");
    for(int i = 0; i < dragImage.size(); i++){
        draggableImage dImg = dragImage[i];
        ofVec2f anchor = dImg.anchorPoint;
        int id = dImg.id;

        settings.addTag("id");
        settings.pushTag("id", i);
        settings.addValue("id", id);
        settings.addValue("anchorPoint_x", anchor.x);
        settings.addValue("anchorPoint_y", anchor.y);
        settings.popTag();

    }

    settings.save("settings.xml");

    cout << "Settings saved to 'settings.xml'" << endl;
}

void ofApp::loadSettings(){
    ofxXmlSettings settings;
    if(settings.loadFile("settings.xml")){
        settings.pushTag("kinects");
        int numKinects = settings.getNumTags("id");
        cout << "Num ID's" << numKinects << endl;
        for(int i = 0; i < numKinects; i++){
            settings.pushTag("id", i);
            int aX = settings.getValue("anchorPoint_x", 0);
            int aY = settings.getValue("anchorPoint_y", 0);
            dragImage[i].anchorPoint.set(aX, aY);
            settings.popTag();
        }

        settings.popTag();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for(int i = 0; i < dragImage.size(); i++){
        dragImage[i].handleMouseDragged(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    for(int i = 0; i < dragImage.size(); i++){
        dragImage[i].handleMousePressed(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for(int i = 0; i < dragImage.size(); i++){
        dragImage[i].handleMouseReleased();
    }
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
