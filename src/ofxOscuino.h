#include "ofMain.h"
#include "ofxNetwork.h"

const char EOT = 192;
const char SLIP_ESC = 219;
const char SLIP_ESC_END = 220;
const char SLIP_ESC_ESC = 221;

class ofxOscuino {
  public:
    void setup(ofSerial&, int, int);
    bool update();

  private:
    void slipDecode(char incoming);
    void slipEncode(char incoming);
    void serialSendToUDP();

    char prevByte;
    ofSerial serial;
    ofxUDPManager udpServer;
    ofxUDPManager udpClient;

    std::vector<char> serialBuffer;    
};