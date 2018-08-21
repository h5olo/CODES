#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cout << "listening for osc message on port" << PORT << "\n";
	receiver.setup(PORT);
	ofEnableAlphaBlending();
	backgroundvideo_1.load("pond.mp4");
	background.load("background.png");
	font.load("verdana.ttf",16);
	infoButton = false; 
	wait = false;
	endTog = false;

	gui.setup();
	gui.setPosition(ofGetWindowWidth() - 300, 150);
	gui.add(scale.setup("SCALE", 0, -100, 100));
	gui.add(depthValue.setup("DEPTH", 1, 0.1, 10));
	gui.add(positionX.setup("POS_X", 0, -1080, 1080));
	gui.add(positionY.setup("POS_Y", 0, -1200, 1200));
	gui.add(interval.setup("INTERVAL", 500, 100, 1000));
	gui.add(maxSrc.setup("maxSrc", 10, 1, 100));
	gui.add(R_x.setup("Rect_X", 0, 0, 1920));
	gui.add(R_y.setup("Rect_Y", 0, 0, 1200));
	gui.add(R_w.setup("Rect_W", 0, 0, 1920));
	gui.add(R_h.setup("Rect_H", 0, 0, 1200));
	gui.add(waitTimer.setup("WAIT_TIMER",10000,1000,20000));

	handLeft_x = 0;
	handLeft_y = 0;
	handLeft_z = 0;

	handRight_x = 0;
	handRight_y = 0;
	handRight_z = 0;

	startTime = ofGetElapsedTimeMillis();
	endTime = 2000;
	Timer = 0;
	sizeMax = 100;
	tracked = 0;

	for (int i = 0; i < 1; i++) {
		auto source = std::make_shared<Particle>();
		//source.get()->setup();
		//sources.push_back(source);
	}


	gui.loadFromFile("settings.xml");
	backgroundvideo_1.play();
}

//--------------------------------------------------------------
void ofApp::update(){
	
	backgroundvideo_1.update();
	for (int i = 0; i < sources.size(); i++) {
		sources[i].get()->update();
	}

	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);

		if (m.getAddress() == "/tracked") {
			tracked = m.getArgAsInt32(0);
		}

		if (m.getAddress() == "/handTipLeft") {
			handLeft_x = ofMap((m.getArgAsInt32(0) + positionX) - scale,0,1920,R_x, (R_x + R_w));
			handLeft_y = ofMap((m.getArgAsInt32(1) + positionY) - scale,0,1200, R_y, (R_y + R_h));
			handLeft_z = m.getArgAsInt32(2)*depthValue;
		}

		if (m.getAddress() == "/HandTipRight") {
			handRight_x = ofMap((m.getArgAsInt32(0) + positionX) + scale,0,1920,R_x, (R_x + R_w));
			handRight_y = ofMap((m.getArgAsInt32(1) + positionY) + scale,0,1200,R_y, (R_y + R_h));
			handRight_z = m.getArgAsInt32(2)*depthValue;
		}
	}

	if (wait == false) {
		if (ofGetMouseX() > R_x && ofGetMouseX() < R_x + R_w && ofGetMouseY() > R_y && ofGetMouseY() < R_y + R_h) {
			sources.push_back(shared_ptr<Particle>(new Particle));
			sources.back().get()->setup();
			sources.back().get()->display(ofGetMouseX(), ofGetMouseY());
			startTime = ofGetElapsedTimeMillis();
		}
	}
	else if (wait == true) {

	}
	

}

//--------------------------------------------------------------
void ofApp::draw() {
	//ofBackground(10);
	
	Timer = ofGetElapsedTimeMillis() - startTime;

	backgroundvideo_1.draw(0, 0);

	for (int i = 0; i < sources.size() ; i++) {
		ofFill();
			sources[i].get()->draw(i,endTog);
		
		if (sources.size() > maxSrc) {
			wait = true;
			if (sources[sources.size() - 1].get()->alpha == 255) {
				endTog = true;
			}
		}

		if (sources[i].get()->clearTog == true) {
			wait = false;
			sources.clear();
			//sources.erase(sources.end() - 1);
		}

		if (sources[i].get()->personalTog == true) {
			wait == false;
			sources.erase(sources.begin());
		
		}

		
	}
	
	ofSetColor(255, 255, 255);
	background.draw(0,0);
	if (infoButton == true) {
		gui.draw();
		font.drawString("Time : " + ofToString(Timer), ofGetWindowWidth() - 200, ofGetWindowHeight() - 100);
		font.drawString("particle Num : " + ofToString(sources.size()),ofGetWindowWidth()-200,ofGetWindowHeight()-120);
		font.drawString("Is Tracked : " + ofToString(tracked), ofGetWindowWidth() - 200, ofGetWindowHeight() - 140);
	//	font.drawString("last Opacity : " + ofToString(sources[0].get()->alpha), ofGetWindowWidth() - 200, ofGetWindowHeight() - 160);
		ofPushStyle();
		ofSetColor(255, 0, 0);
		ofDrawCircle(handLeft_x, handLeft_y, 10, 10);
		ofDrawCircle(handRight_x, handRight_y, 10, 10);
		ofPopStyle();
		ofNoFill();
		ofDrawRectangle(R_x, R_y,R_w,R_h);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'q') {
		if (sources.size() < maxSrc) {
			endTog = false;
			sources.push_back(shared_ptr<Particle>(new Particle));
			sources.back().get()->setup();
			sources.back().get()->display(ofGetMouseX(), ofGetMouseY());
		}
		else {
			endTog = true;
		}
	}
	if (key == 'c') {
		
		sources.clear();
	}

	if (key == 'i') {
		infoButton = true;
	}

	if (key == 'o') {
		infoButton = false;
	}

	if (key == 's') {
		gui.saveToFile("settings.xml");
	}

	if (key == 'l') {
		gui.loadFromFile("setting.xml");
	}

	if (key == 'r') {
		gui.loadFromFile("reset.xml");
	}

	if (key == 't') {
		startTime = ofGetElapsedTimeMillis();
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
