These project files will allow you to decode an IR pulse.

IRIn contains the code that is loaded on the Arduino or DIY Arduino.  It uses 2 libraries: 
<ul>
  <li>TimerOne which is a timer class, running every 50 microseconds</li>
  <li>IR which contains the callback procedure that is called from Timer1 and collects the raw data</li>
</ul>

Note:
   The input pin that is used in this example is D10 which matches the DIYIRArduino IR receiver output.