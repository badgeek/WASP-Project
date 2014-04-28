#include "samplespot.h"

sampleSpot::sampleSpot(int x, int y)
{

    imgMarker.loadImage("waspMarker.png");

    pos.set(x,y);
    diameter = 0;
    textPos = 10;

    unsigned delay = 2000;
    unsigned duration = 1000;
    Tweener.addTween(diameter, 10, 5, &ofxTransitions::easeOutElastic);
    Tweener.addTween(textPos, 40, 5);
    //tweenlinear.setParameters(7,easinglinear,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);

    sampleName = "Sample Point";
}
void sampleSpot::update()
{

}

void sampleSpot::draw()
{

    ofPushStyle();
    ofSetColor(246,212,77);
    ofDrawBitmapString(sampleName, pos.x + textPos, pos.y-30,0);
    ofFill();
    ofSetLineWidth(2.0);
    ofLine(pos.x,pos.y,pos.x + textPos, pos.y-30);
    ofCircle(pos,diameter);
    ofPopStyle();

//    imgMarker.draw(pos.x-25,pos.y-66,0);

}

sampleSpot::~sampleSpot()
{
    Tweener.removeTween(diameter);
    Tweener.removeTween(textPos);
}
