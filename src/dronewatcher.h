#ifndef DRONEWATCHER_H
#define DRONEWATCHER_H

#include "ofMain.h"
#include "drone.h"
#include "samplespot.h"
#include "sampletube.h"

#include <vector>

#include "ofLog.h"
using namespace std;

class DroneWatcher
{
public:
    DroneWatcher();
    DroneWatcher(Drone *drone);
    void draw();
    void setup(Drone *drone);

    float droneLastDistance;

    Drone* myDrone;

    vector<int> vectorOne;
    vector<sampleSpot*> sampleSpots;
    vector<sampleTube*> sampleTubes;
    float sampleTubePosX;


    ofEvent<void> EventSampleSpot;


    void clearSpots();
    ~DroneWatcher();
    void update();
    void clearAll();
};

#endif // DRONEWATCHER_H
