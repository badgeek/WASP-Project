#ifndef SAMPLESPOT_H
#define SAMPLESPOT_H

#include "ofMain.h"
#include "ofxTweener.h"

class sampleSpot
{
public:
    sampleSpot(int x , int y);
    ofPoint pos;

    float textPos;
    float tubeLevel;

    float diameter;
    void draw();

    string sampleName;

    void update();
    ~sampleSpot();

    ofImage imgMarker;
};

#endif // SAMPLESPOT_H
