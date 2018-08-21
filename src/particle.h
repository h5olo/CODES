#ifndef _PARTICLE
#define _PARTICLE

#include "ofMain.h"
#include "ofxImageSequencePlayback.h"

class Particle {

public:
	Particle();

	void setup();
	void update();
	void display(float mouseX, float mouseY);
	void draw(int i, bool endTog);

	float x;
	float y;
	int r;
	int randomR;
	int alpha;
	float speedX;
	float speedY;
	
	bool clearTog;
	bool personalTog;

	ofxImageSequencePlayback effect;
	ofTrueTypeFont font;
	int ix, iy;
};
#endif