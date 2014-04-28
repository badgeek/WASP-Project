#include "drone.h"

Drone::Drone()
{
    timeCounter = 0;
    timeOfLastFrame = 0;

    prevpos.set(0,0);
    pos.set(0,0);
    restartPos = false;
    prevRestartPos = false;
    beginningPos = true;

    totalDistance = 0;

    imgWaspDirection.loadImage("waspDirection.png");
}

void Drone::update()
{
    // figure out how much time elapsed from frame to frame:
    float diffTime		= ofGetElapsedTimef() - timeOfLastFrame;
    timeOfLastFrame		= ofGetElapsedTimef();
    timeCounter			+= diffTime;

    //if (totalDistance == 0.0 ) prevpos.set(PR.getPointForTime(timeCounter).x,PR.getPointForTime(timeCounter).y);

    if (PR.bAmRecording == false && PR.pts.size() > 1)
    {
        ofPoint posxy = PR.getPointForTime(timeCounter);


        if(totalDistance == 0 && beginningPos == true)
        {
            prevpos.set(posxy.x, posxy.y);
            beginningPos = false;
        }

        pos.set(posxy.x, posxy.y);
        dist = pos-prevpos;
        angle = prevpos.angle(dist);
        totalDistance += dist.length();
        prevpos = pos;
    }
}

void Drone::draw()
{
    PR.draw();
    //ofDrawBitmapString("dist: " + ofToString(totalDistance) + " angle: " + ofToString(angle),200,200,0);
    if (PR.bAmRecording != true)
    {
    ofPushStyle();
    //ofSetColor(255,0,0);
    ofFill();

    ofPushMatrix();
    ofTranslate(pos.x,pos.y,0);
    ofPushMatrix();
        //ofVec2f arrow;
        //arrow = pos + (dist.normalized()*20);
        ofRotateZ(angle+45);
        //ofRect(0,0,10,5);
        //ofDrawRotationAxes(100);
imgWaspDirection.draw(-44.5,-32.0,0);
        //ofLine(pos.x,pos.y,arrow.x,arrow.y);
        //ofRectangle(pos.x, pos.y,20,10);
    ofPopMatrix();
    ofPopMatrix();
    ofPopStyle();

    ofCircle(pos.x, pos.y, 2);
    }
}

void Drone::setup()
{
    timeCounter			= 0;
    timeOfLastFrame		= ofGetElapsedTimef();
    ofAddListener(PR.EventRestartedFromBeginning, this, &Drone::resetDistance);
}


void Drone::resetDistance()
{
    beginningPos = true;
    totalDistance = 0;
    ofNotifyEvent(restartPosition, this);
}

void Drone::addPoint(ofPoint pt)
{
    PR.bAmRecording = true;
    PR.addPointConstant(pt);
    PR.bAmRecording = false;
}

void Drone::reset()
{
    PR.clear();
}

void Drone::startRecord()
{
    PR.clear();
    PR.bAmRecording = true;
}

void Drone::stopRecord()
{
    PR.bAmRecording = false;
    timeCounter = 0;
}

Drone::~Drone()
{
   // ofRemoveListener(PR.EventRestartedFromBeginning,this, &Drone::resetDistance);
}
