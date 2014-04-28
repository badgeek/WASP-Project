#include "pointRecorder.h"


//------------------------------------------------------------------
pointRecorder::pointRecorder(){
	maxNumPts = 500;  // try 50, for example....
    startTime = 0;
    constantTime = 0;
    firstPos = true;
    bReposition = false;
}

//------------------------------------------------------------------
void pointRecorder::draw() {
	
    ofPushStyle();
	//---------------------------
	// (a) create a small report 
    ofSetColor(255,255,255);
    ofSetLineWidth(5.0);
	// get the number of points and the time of the last point:
	int nPts = pts.size();
	float totalDuration = getDuration();
    //string report = "nPts = " + ofToString(nPts) + "\ntotal time = " + ofToString(totalDuration, 3);
    //ofDrawBitmapString(report, 10, 10);
	
	//---------------------------
	// (b) draw the line: 
	if (bAmRecording)		ofSetColor(255,255,0);
    else					ofSetColor(255,255,255);
		
	ofNoFill();
	ofBeginShape();
	for (int i = 0; i < pts.size(); i++){
		ofVertex(pts[i].pos.x, pts[i].pos.y);
	}
	ofEndShape(false);
    ofPopStyle();
}

//------------------------------------------------------------------
void pointRecorder::addPointConstant(ofPoint pt) {
	
	
	// on the first point, grab the start time
	if (pts.size() == 0){
        constantTime = 0;
	} 
	
    constantTime += 0.2;
	
	// combine the position and the time here: 
	timePt	myPoint;
	myPoint.pos			= pt;
    //myPoint.time		= ofGetElapsedTimef() - startTime;
    myPoint.time		= constantTime;

	cout << "creating point " << pts.size() << " at time: " << myPoint.time << endl;

	pts.push_back(myPoint);
	if (pts.size() > maxNumPts){
		pts.erase(pts.begin());
	}
}

void pointRecorder::addPoint(ofPoint pt) {


    // on the first point, grab the start time
    if (pts.size() == 0){
        startTime = ofGetElapsedTimef();
    }


    // combine the position and the time here:
    timePt	myPoint;
    myPoint.pos			= pt;
    myPoint.time		= ofGetElapsedTimef() - startTime;

    cout << "creating point " << pts.size() << " at time: " << myPoint.time << endl;

    pts.push_back(myPoint);
    if (pts.size() > maxNumPts){
        pts.erase(pts.begin());
    }
}


//------------------------------------------------------------------
void pointRecorder::clear() {
	pts.clear();
}

//------------------------------------------------------------------
float pointRecorder::getDuration() {
	float totalDuration = 0;
	if (pts.size() > 0){
		totalDuration = pts[pts.size() - 1].time;
	}
	return totalDuration;
}

ofPoint pointRecorder::getPointForTime(float time){
	
	// ok here's how to do it.
	// (a) if we have no points, or one point, or are recording return nothing...
	
	if (pts.size() <= 1 || bAmRecording) return ofPoint(0,0,0); 
	

	// (b) else, find out where we are for a given time 
	// do something like a % operator with the time, 
	// easier to see it in integer math:
	// for example, if our total time is 3, and we look for time 0, we are at time 0
	// if we look at 1, we are at time 1  (1 % 3)
	// if we look at 2, we are at time 2  (2 % 3)
	// if we look at 3, we are at time 0  (3 % 3)
	// if we look at 4, we are at time 1  (4 % 3)
	// (ie, we use mod to wrap over)
	// for example, if are at time 11, we do 11 % 3, which equals 2, so we are at time 2....
	
	// now, we do that with floats, like this:
	float totalTime = getDuration();
	float timeInRange = time;
	while (timeInRange > totalTime){
		timeInRange -= totalTime;
	}
	
	// ok we are looking for a point whose time is greater then timeInRange...
	int whatPointAmINear = 0;
	for (int i = 0; i < pts.size(); i++){
		if (pts[i].time > timeInRange){
			whatPointAmINear = i;
			break; // leave the for loop :)
		}
	}
	
	// now, if that point is greater then 0, we will linearly interpolate
	// else return pt0
	

    if (whatPointAmINear > 0){
        restartPos = false;
    }else{
        restartPos = true;
    }

    if (restartPos != prevRestartPos)
    {
        if (whatPointAmINear == 0 )
        {
            if (!firstPos)
            {
                bReposition = true;
                ofLog() <<"RESTART POS";
                ofNotifyEvent(EventRestartedFromBeginning,this);

            }else{
                ofLog() <<"FIRST POS";
                bReposition = false;
                //ofNotifyEvent(EventRestartedFromBeginning,this);
            }
            firstPos = false;
        }
    }

    prevRestartPos = restartPos;


	if (whatPointAmINear > 0){
		float timea = pts[whatPointAmINear - 1].time;
		ofPoint pta = pts[whatPointAmINear - 1].pos;
		float timeb = pts[whatPointAmINear    ].time;
		ofPoint ptb = pts[whatPointAmINear    ].pos;
		float totalDurationBetweenThesePts	= timeb - timea;
		float myPositionBetweenThesePts		= timeInRange - timea;
		float pct = myPositionBetweenThesePts / totalDurationBetweenThesePts; 
		ofPoint mix(0,0,0);
		mix.x = (1-pct) * pta.x + (pct) * ptb.x;
		mix.y = (1-pct) * pta.y + (pct) * ptb.y;

		return mix;
	} else {
		return pts[whatPointAmINear].pos;
	}
	
	
}
