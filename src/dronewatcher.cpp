#include "dronewatcher.h"

DroneWatcher::DroneWatcher()
{
    droneLastDistance = 0;
    sampleTubePosX = 0;
}

DroneWatcher::DroneWatcher(Drone *drone)
{
    DroneWatcher();
    setup(drone);
}

void DroneWatcher::update()
{
    int testx;
    if ( (myDrone->totalDistance - droneLastDistance  > 300.0) && (int) myDrone->totalDistance != 0)
    {

        sampleTubePosX += 70;
        droneLastDistance = myDrone->totalDistance;


        string sampleName = "Tube-" + ofToString(sampleTubes.size());

        sampleSpot * spot = new sampleSpot(myDrone->pos.x, myDrone->pos.y);
        spot->sampleName = "Tube-" + ofToString(sampleSpots.size());
        sampleSpots.push_back(spot);

        if (sampleTubes.size() < 19)
        {
            sampleTube * tube = new sampleTube(sampleTubePosX, ofGetHeight()-80);
            tube->fill();
            tube->TubeName = sampleName;
            sampleTubes.push_back(tube);
        }

        ofNotifyEvent(EventSampleSpot, this);
    }

    for(int i = 0; i<sampleSpots.size(); i++){
        sampleSpots.at(i)->update();
    }

    myDrone->update();
}

void DroneWatcher::draw()
{
    ofDrawBitmapString("Start Position", myDrone->PR.pts.at(0).pos.x,myDrone->PR.pts.at(0).pos.y);
    int lasPos = myDrone->PR.pts.size() -1;
    ofDrawBitmapString("End Position", myDrone->PR.pts.at(lasPos).pos.x,myDrone->PR.pts.at(lasPos).pos.y);

    myDrone->draw();

    for(int i = 0; i<sampleSpots.size(); i++){
        sampleSpots.at(i)->draw();
    }


    ofPushMatrix();
    ofTranslate(50,0,0);
    for(int j = 0; j<sampleTubes.size(); j++){
        sampleTubes.at(j)->draw();
    }
    ofPopMatrix();



}

void DroneWatcher::setup(Drone *drone)
{
    myDrone = drone;
    ofAddListener(myDrone->restartPosition,this, &DroneWatcher::clearSpots);
}

void DroneWatcher::clearSpots()
{
    sampleSpots.clear();
    sampleTubes.clear();
    sampleTubePosX = 0;
    droneLastDistance = 0;
}

void DroneWatcher::clearAll()
{
    clearSpots();
    myDrone->timeCounter = 0;
    myDrone->timeOfLastFrame = ofGetElapsedTimef();
    myDrone->PR.clear();
    myDrone->resetDistance();

}

DroneWatcher::~DroneWatcher()
{
    ofRemoveListener(myDrone->restartPosition,this,&DroneWatcher::clearSpots);
}
