#include "testApp.h"
#include "ofMain.h"

//--------------------------------------------------------------
void testApp::setup(){

    //ofEnableDepthTest();
    // this sets the camera's distance from the object
    ofEnableSmoothing();

    MapFile = "Drone_Path_1.xml";

    //cam.enableOrtho();
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0,0,0);

    lastTagNumber       = 0;

    JRP_DRONE.setup();
    DRONE_WATCHER.setup(&JRP_DRONE);

   // MapXML.getValue("device", "/dev/")
    loadXML();

    SettingsXML.loadFile("Settings.xml");

    string ardDevice = SettingsXML.getValue("DEVICE", "/dev/cu.usbserial-A5029U9R");

    ofLog() << ardDevice;

    ard.connect(ardDevice, 57600);
    ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
    bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)


    ardTimer.setup(5000);
    ofAddListener(ardTimer.TIMER_STARTED,this, &testApp::arduinoTimerStartedHandler);
    ofAddListener(ardTimer.TIMER_COMPLETE,this, &testApp::arduinoTimerFinishedHandler);



    idleTimer.setup(60000 * 1);
    //ofAddListener(idleTimer.TIMER_STARTED, this, &testApp::idleTimerFinishedHandler);

    ofAddListener(idleTimer.TIMER_COMPLETE, this, &testApp::idleTimerFinishedHandler);

    ofAddListener(DRONE_WATCHER.EventSampleSpot,this,&testApp::droneWatcherAddSpotHandler);

    imgWaspLogo.loadImage("waspLogo.png");
  //  imgWaspBG.loadImage("waspBG.png");

    isRecording = false;

}

//--------------------------------------------------------------
void testApp::update(){
    DRONE_WATCHER.update();
    ardTimer.update();
    idleTimer.update();
    Tweener.update();
}

//--------------------------------------------------------------
void testApp::draw(){
//    ofTranslate(0,0,1);
   // imgWaspBG.draw(0,0,0,1024,768);


    imgWaspLogo.draw(ofGetWidth()/2 - (imgWaspLogo.width/2),20);
    ofPushStyle();

    ofNoFill();
    ofSetColor(246,212,77);
    ofSetLineWidth(8);
    ofRect(80,150,ofGetWidth()-160,500);
    ofDrawBitmapString("Drone Position: X" + ofToString(JRP_DRONE.pos.x)  + " Y" + ofToString(JRP_DRONE.pos.y) +"\nSample Count: " + ofToString(DRONE_WATCHER.sampleTubes.size()),80, 680 );
    ofPopStyle();
        DRONE_WATCHER.draw();

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    if (key == 'f') ofToggleFullscreen();
    if (key == 's') MapXML.saveFile(MapFile);

    if (key =='1') 	ard.sendDigital(2, ARD_HIGH);
    if (key =='2') 	ard.sendDigital(3, ARD_HIGH);
    if (key =='3') 	ard.sendDigital(4, ARD_HIGH);
    if (key =='4') 	ard.sendDigital(5, ARD_HIGH);


    if (key =='t') 	ard.sendDigital(13, ARD_HIGH);


    if (key == 'p') DRONE_WATCHER.sampleSpots.push_back(new sampleSpot(JRP_DRONE.pos.x, JRP_DRONE.pos.y));
    if (key == 'r') loadXML();

}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

    if (key =='1') 	ard.sendDigital(2, ARD_LOW);
    if (key =='2') 	ard.sendDigital(3, ARD_LOW);
    if (key =='3') 	ard.sendDigital(4, ARD_LOW);
    if (key =='4') 	ard.sendDigital(5, ARD_LOW);

    if (key =='t') 	ard.sendDigital(13, ARD_LOW);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    idleTimer.start(false,true);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

    if (x>80 && y >150 && (x < (ofGetWidth()-160)) && y < 650 && isRecording)
    {
        JRP_DRONE.addPoint(ofPoint(x,y,0) );
        if( MapXML.pushTag("STROKE", lastTagNumber) ){
            int tagNum = MapXML.addTag("PT");
            MapXML.setValue("PT:X", x, tagNum);
            MapXML.setValue("PT:Y", y, tagNum);
            MapXML.popTag();
        }
    }


}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if (x>80 && y >150 && (x < (ofGetWidth()-160)) && y < 650)
    {
    isRecording = true;
    JRP_DRONE.reset();
    JRP_DRONE.addPoint(ofPoint(x,y));
    MapXML.clear();
    lastTagNumber	= MapXML.addTag("STROKE");
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    JRP_DRONE.stopRecord();
    isRecording = false;

}

void testApp::arduinoTimerStartedHandler(int &args)
{
    ofLog() << "arduino on";
    ard.sendDigital(13, ARD_HIGH);
}

void testApp::arduinoTimerFinishedHandler(int &args)
{
    ofLog() << "arduino off";
    ard.sendDigital(13, ARD_LOW);
    ardTimer.stop();
}

void testApp::idleTimerFinishedHandler(int &args)
{
    ofLog() << "Idle detected, reset point";
    loadXML();
}

void testApp::arduinoTimerHandler(int &args)
{

}

void testApp::droneWatcherAddSpotHandler()
{
    ofLog() << "drone watcher event";
    ardTimer.start(false);
}

void testApp::loadXML()
{
    MapXML.clear();
    MapXML.loadFile(MapFile);
    DRONE_WATCHER.clearAll();
    int numDragTags = MapXML.getNumTags("STROKE:PT");
    if(numDragTags > 0){
        //we push into the last STROKE tag
        //this temporarirly treats the tag as
        //the document root.
        MapXML.pushTag("STROKE", numDragTags-1);
            //we see how many points we have stored in <PT> tags
            int numPtTags = MapXML.getNumTags("PT");
            if(numPtTags > 0){
                int totalToRead = MIN(numPtTags, 1000);
                for(int i = 0; i < totalToRead; i++){
                    int x = MapXML.getValue("PT:X", 0, i);
                    int y = MapXML.getValue("PT:Y", 0, i);
                    JRP_DRONE.addPoint(ofPoint(x,y,0) );
                }
            }
        MapXML.popTag();
    }
}

void testApp::setupArduino(const int &version)
{
    bSetupArduino = true;
    ard.sendDigitalPinMode(13, ARD_OUTPUT);
    ard.sendDigitalPinMode(2,  ARD_OUTPUT);
    ard.sendDigitalPinMode(3,  ARD_OUTPUT);
    ard.sendDigitalPinMode(4,  ARD_OUTPUT);
    ard.sendDigitalPinMode(5,  ARD_OUTPUT);

    ofLog() << "Arduino Setup OK";
}


//--------------------------------------------------------------
