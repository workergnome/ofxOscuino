#include "ofMain.h"
#include "ofxNetwork.h"


class SLIPSerial {
  public:
    void setup(ofSerial&, int, int);
    bool checkForData();
  private:
    void slipDecode(char incoming);
    void slipEncode(char incoming);
    void serialSendToUDP();

    const char EOT = 192;
    const char SLIP_ESC = 219;
    const char SLIP_ESC_END = 220;
    const char SLIP_ESC_ESC = 221;
    char prevByte;
    ofSerial serial;
    ofxUDPManager udpServer;
    ofxUDPManager udpClient;

    std::vector<char> serialBuffer;
    
};