#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxOsc.h"
#include "ofxOscuino.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);

		ofxOscReceiver receiver;
		ofxOscSender sender;
		ofSerial serial;
		ofxOscuino oscBridge;
};
