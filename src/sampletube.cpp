#include "sampletube.h"

sampleTube::sampleTube(float x, float y)
{
    tubeLevel = 0;
    posX = x;
    posY = y;
    TubeName = "Tube";

    imgTube.loadImage("waspTube.png");
}


void sampleTube::update()
{

}

void sampleTube::fill()
{
    Tweener.addTween(tubeLevel, 54, 5);
}


void sampleTube::draw()
{
    ofPushMatrix();
        ofTranslate(posX-50,posY+20,0);
        ofDrawBitmapString(TubeName,0,0,0);
    ofPopMatrix();

    ofPushMatrix();
    ofTranslate(posX,posY,0);
        ofPushMatrix();
        ofPushStyle();
            ofRotateZ(180);
            ofNoFill();
            imgTube.draw(0,0,0);
            //ofRect(0,0,0,30,100);
            ofFill();
            ofSetColor(246,212,77);
            ofRect(12,22,0,24,tubeLevel);
         ofPopStyle();
        ofPopMatrix();
    ofPopMatrix();
}

sampleTube::~sampleTube()
{
    Tweener.removeTween(tubeLevel);
}
