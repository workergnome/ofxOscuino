#include <OSCBundle.h>
#include <OSCMessage.h>


#ifdef BOARD_HAS_USB_SERIAL
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
#include <SLIPEncodedSerial.h>
 SLIPEncodedSerial SLIPSerial(Serial);
#endif

bool toggles = false;

void testFunction(OSCMessage &msg)
{
  int testVal = msg.getInt(0);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, (toggles? HIGH: LOW));
  toggles = !toggles;
  
  OSCMessage resp("/response");
  resp.add(testVal);

  SLIPSerial.beginPacket();  
  resp.send(SLIPSerial); // send the bytes to the SLIP stream
  SLIPSerial.endPacket(); // mark the end of the OSC Packet
  resp.empty(); // free space occupied by message
}

void setup() {
  // put your setup code here, to run once:
    SLIPSerial.begin(9600);   // set this as high as you can reliably run on your platform
#if ARDUINO >= 100
    while(!Serial)
      ;   // Leonardo bug
#endif
}


void loop() {
  OSCBundle bundleIN;
  int size;

  while(!SLIPSerial.endofPacket())
    if( (size =SLIPSerial.available()) > 0)
    {
       while(size--)
          bundleIN.fill(SLIPSerial.read());
     }
  
  if(!bundleIN.hasError())
     bundleIN.dispatch("/test", testFunction);
}
