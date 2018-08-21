#include "particle.h"


Particle::Particle() {
}

void Particle::setup() {
	effect.loadSequence("sequence", 24.0f);

	font.load("verdana.ttf", 20);

	ix = 0;
	iy = 0;
	alpha = 0;
	randomR = ofRandom(80, 150);
	//clearTog = false;
	personalTog = false;
}

void Particle::draw(int i, bool endTog) {
	effect.draw(x , y , randomR, randomR, alpha);

	y = y + 2;
	if (y > ofGetWindowHeight()-200) {
		personalTog = true;
	}
	else {
		personalTog = false;
	}

	if (alpha < 255 && endTog == false) {
		alpha = alpha + 10;
	}
	else if(alpha > 255){
	alpha = 255;
	
}
	if (endTog == true) {
		alpha = alpha - 5;
		if (alpha < 0) {
			clearTog = true;
			alpha = 0;
			clearTog = false;
		}
	}
	
	//font.drawString(ofToString(effect.getCurrentFrameIndex()), x - 100, y - 100);
	//font.drawString("index[" + ofToString(i) + "]",x+150,y-100);
}

void Particle::update() {

	effect.update();

	if (effect.getCurrentFrameIndex() == 119) {
	//	effect.stop();
	//	effect.setCurrentFrameIndex(13);
		effect.pause();
	}
}
void Particle::display(float mouseX, float mouseY) {
	x = mouseX-100;
	y = mouseY-100;
	effect.play();
	
}
