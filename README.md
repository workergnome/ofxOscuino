Introduction
------------
ofxOscuino is a quick and dirty [OpenFrameworks](http://openframeworks.cc) addon for using the [Oscuino](http://cnmat.berkeley.edu/oscuino) library for [OSC](http://opensoundcontrol.org) on [Arduino](http://www.arduino.cc).  It works as a bridge between the serial port and the UDP libraries. 

It does this by creating a SLIP bridge and sending the OSC messages over serial to the arduino.  Any messages sent back will be converted back into OSC and sent over the UDP port back to the application.  While this is certainly not the most efficient way to do so, it lets all the existing OpenFrameworks OSC stuff work out of the box.

Included in the example is a very basic example Arduino sketch, called `ofxOscuinoArduinoExample`.  This will require that you have installed the [Oscuino Arduino Library](https://github.com/CNMAT/OSC) into your installation of Arduino.


License
------------
This addon is distributed under the [MIT License](https://en.wikipedia.org/wiki/MIT_License).

Dependencies
------------
This addon uses the serial library from `ofxNetwork`.
The example also uses `ofxOsc`, obviously, though the library doesn't depend on it.

Compatibility
------------
This has been tested with Open Frameworks 8.4 on OSX.  It's also only been tested with an Arduino Uno.

Known issues
------------
None as of yet.  That will likely change.


Version history
------------

### Version 0.1 (April 20, 2015):
Initial release.
