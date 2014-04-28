#ifndef DRONE_H
#define DRONE_H
#include "ofMain.h"
#include "pointRecorder.h"
#include "ofVec2f.h"
#include "ofEvents.h"

class Drone
{
public:
    Drone();

    ofVec2f prevpos;
    ofVec2f pos;
    ofVec2f dist;

    float angle;

    pointRecorder	PR;

    float totalDistance;

    float			timeCounter;
    float			timeOfLastFrame;

    bool restartPos;
    bool prevRestartPos;
    bool beginningPos;

    void update();
    void draw();
    void setup();

    void stopRecord();
    void startRecord();

    void addPoint(ofPoint pt);
    void reset();
    void resetDistance();

    ofImage imgWaspDirection;

    ofEvent<void> restartPosition;

    ~Drone();
};

#endif // DRONE_H
