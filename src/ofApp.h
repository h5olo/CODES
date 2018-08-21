#pragma once

#include "ofMain.h"
#include "particle.h"
#include "ofxOsc.h"
#include "ofxGui.h"

#define PORT 12345
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		vector <shared_ptr<Particle> > sources;
		
		ofVideoPlayer testVid;

		float handLeft_x, handLeft_y, handLeft_z;
		float handRight_x, handRight_y, handRight_z;
		float startTime, endTime, Timer;
		int tracked;

		ofTrueTypeFont font;
		ofxOscReceiver receiver;

		ofVideoPlayer backgroundvideo_1;

		int current_msg_string;
		int sizeMax;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];

		string jointName;
		string mouseButtonState;

		ofxFloatSlider scale;
		ofxIntSlider positionX;
		ofxIntSlider positionY;
		ofxIntSlider maxSrc;
		ofxIntSlider interval;
		ofxIntSlider R_x, R_y, R_w, R_h;
		ofxIntSlider waitTimer;
		ofxFloatSlider depthValue;
		ofxPanel gui;
		ofImage background;

		bool infoButton;
		bool wait;
		bool endTog;

};
