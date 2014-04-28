#ifndef SAMPLETUBE_H
#define SAMPLETUBE_H

#include "ofMain.h"
#include "ofxTweener.h"

class sampleTube
{
public:
    sampleTube();
    sampleTube(float x, float y);
    void update();
    void draw();

    float width;
    float height;

    void fill();

    ofRectangle test;
    string TubeName;

    float tubeLevel;
    float posX;
    float posY;

    ofImage imgTube;

    ~sampleTube();
};

#endif // SAMPLETUBE_H
