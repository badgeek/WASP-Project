#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofLog.h"
#include "ofxXmlSettings.h"
#include "ofEvents.h"
#include "ofxSimpleTimer.h"

#include "drone.h"
#include "dronewatcher.h"
#include "pointRecorder.h"
#include "samplespot.h"
class testApp : public ofSimpleApp{

    public:

        void setup();
        void update();
        void draw();

        void keyPressed  (int key);
        void keyReleased (int key);

        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);

        void mouseReleased(int x, int y, int button);


        void arduinoTimerStartedHandler(int &args);
        void arduinoTimerFinishedHandler(int &args);

        void idleTimerFinishedHandler(int &args);

        ofxXmlSettings MapXML;
        ofxXmlSettings SettingsXML;

        int lastTagNumber;

        string MapFile;
        string ArduinoDevice;

        Drone JRP_DRONE;
        DroneWatcher DRONE_WATCHER;

        ofArduino ard;
        ofEasyCam cam;
        ofxSimpleTimer ardTimer;
        ofxSimpleTimer idleTimer;

        ofImage imgWaspBG;
        ofImage imgWaspLogo;

        bool isRecording;

        void arduinoTimerHandler(int &args);
        void droneWatcherAddSpotHandler();


        void loadXML();

private:
        void setupArduino(const int & version);
        bool bSetupArduino;

};

#endif

