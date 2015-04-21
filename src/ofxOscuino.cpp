#include "ofxOscuino.h"

void ofxOscuino::setup(ofSerial &_serial, int serverPort, int clientPort) {
  serial = _serial;
  udpServer.Create();
  udpServer.Connect("127.0.0.1",serverPort);
  udpServer.SetNonBlocking(true);

  udpClient.Create();
  udpClient.SetNonBlocking(true);

  bool clientConnected = udpClient.Bind(clientPort);
  if (!clientConnected) {
    ofLog(OF_LOG_ERROR) << "Could not connect to the client!";
  } else {
    ofLog(OF_LOG_NOTICE) << "Connected to Client Successfully.";
  }
}

void ofxOscuino::slipDecode(char incoming) {
  char previous = prevByte;
  prevByte = incoming;
  //if the previous was the escape char
  if (previous == SLIP_ESC) {
    //if this one is the esc eot
    if (incoming == SLIP_ESC_END) {
      serialBuffer.push_back(EOT);
    }
    else if (incoming==SLIP_ESC_ESC) {
      serialBuffer.push_back(SLIP_ESC);
    }
  }
  else if (incoming==EOT) {
    //if it's the eot
    //send off the packet
    serialSendToUDP();
  }
  else {
    serialBuffer.push_back(incoming);
  }
}

void ofxOscuino::slipEncode(char incoming) {
  if(incoming == EOT){
    serial.writeByte(SLIP_ESC);
    serial.writeByte(SLIP_ESC_END);
  } else if(incoming==SLIP_ESC) {
    serial.writeByte(SLIP_ESC);
    serial.writeByte(SLIP_ESC_ESC);
  } else {
    serial.writeByte(incoming);
  }
}

void ofxOscuino::serialSendToUDP() {
  udpServer.Send(serialBuffer.data(),serialBuffer.size());
  serialBuffer.clear();
}

bool ofxOscuino::update() {
  //handle the serial port
  char myByte;
  myByte = serial.readByte();
  while (myByte != OF_SERIAL_NO_DATA) {
    if ( myByte != OF_SERIAL_ERROR ) {
      slipDecode(myByte);
    }
      else {
        ofLog(OF_LOG_ERROR) << "Whoops!  USB might be disconnected.";
        return false;
      }
    myByte = serial.readByte();
  }
  // handle the upd port
  char udpMessage[100000];
  int receivedSize = udpClient.Receive(udpMessage,100000);
  if(receivedSize > 0) {
    for (int i = 0; i <receivedSize; i++){
      slipEncode(udpMessage[i]);
    }
    serial.writeByte(EOT);
  }
  return true;
}