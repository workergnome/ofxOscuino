/* 

This example is a very, very simple message sending application.  It's designed to be 
paired with an arduino, connected via serial, running the ofxOscuinoArduinoExample
arduino sketch found in this directory.

On any keypress, it will send the char value as of that key as an integer to the "/test"
address.  The arduino sketch should both toggle the built-in LED and echo the integer back.

*/
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetLogLevel(OF_LOG_VERBOSE);

  int receivePort = 11999;  // This is the port that bridge will be sending messages on,
                            // and openFrameworks will be listening on.

  int sendPort    = 11998;  // This is the port that the bridge will be listening on, 
                            // and openFrameworks will be sending messages on.

  int arduinoBaud = 9600;   // This is the baud rate that the arduino's serial 
                            // will be listening on.
  
  int serialNum   = 0;      // This is the integer of the serial device that the
                            // arduino is assigned.  See the communication/serialExample
                            // for more information on how to determine what this is.

  // Set up the OSC sender and receiver
  receiver.setup(receivePort);
  sender.setup("127.0.0.1", sendPort);

  // Set up the serial port
  serial.setup(serialNum, arduinoBaud);
  serial.flush();

  //Set up ofxOscuino
  oscBridge.setup(serial,receivePort,sendPort);

  // Make it pretty
  ofBackground(30, 130, 30);
}

//--------------------------------------------------------------
void ofApp::update(){

  // Get data from the UDP-Serial bridge if both the serial is initialized 
  // and the bridge is working

  if(serial.isInitialized() && oscBridge.update()) {
    while(receiver.hasWaitingMessages()) {
      // get the next message
      ofxOscMessage m;
      receiver.getNextMessage(&m);

      // On any received message, print the address and the first 
      // value of the message (as an int) to the log.
      ofLog(OF_LOG_NOTICE) << "address:" << m.getAddress() << ", message: " << m.getArgAsInt32(0);
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  
  ofSetColor(255);
  ofDrawBitmapString("Watch the log.", 20,20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

  // If the serial system is initialized,
  if (serial.isInitialized()) {

    // compose an OSC message
    ofxOscMessage msg;
    msg.setAddress("/test");
    msg.addIntArg(key);

    // send that message over OSC via the ofxOscSender sender.
    sender.sendMessage(msg);
    ofLog(OF_LOG_VERBOSE) << "trying to send '" << key << "'";
  }
  else {
    ofLog(OF_LOG_ERROR) << "Could not send OSC message.  The serial is not yet initialized.";
  }
}
