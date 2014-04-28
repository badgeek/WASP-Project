#ifndef POINT_RECORDER_H
#define POINT_RECORDER_H

#include "ofMain.h"
#include "ofLog.h"
#include "ofEvents.h"

// ---------------------------
// this is like an old school class, a "struct"
// it doesn't have functions, just data...
// it's C style -
//
// typedef 
// http://bytes.com/forum/thread620088.html
// http://en.wikipedia.org/wiki/Typedef
// struct
// http://www.itee.uq.edu.au/~comp2303/Leslie_C_ref/C/SYNTAX/struct.html
// http://en.wikipedia.org/wiki/C%2B%2B_structures_and_classes


typedef struct {
	ofPoint		pos;
	float		time; // from the start, what time does this pt occur at	
} timePt;



class pointRecorder {

	public:
	
        pointRecorder();
	
		void addPoint(ofPoint pt);
		void clear();
		void draw();
		float getDuration();
		

		ofPoint getPointForTime(float time);
	
		float				startTime;
		int					maxNumPts;
        float               constantTime;
		vector <timePt>		pts;
	
		bool				bAmRecording;			// we don't playback when we are recording...
        bool                restartPos;
        bool                prevRestartPos;

        bool                bReposition;
        bool                firstPos;

        ofEvent<void>       EventRestartedFromBeginning;

        void addPointConstant(ofPoint pt);
};

#endif // POINT_RECORDER_H
