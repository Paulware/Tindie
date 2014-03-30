This example will show how to control an RGB LED using an Android device.  <p><b>The overview of this activity is:</b>
<ul>
<li>Download the ADT Bundle which contains Eclipse with Android SDK on your computer.  This will allow you to edit and upload the android program written in java.</li>
<li>Install windows drivers for your Android device.</li>
<li>Download the java Android program from github and upload to your Android device.</li>
<li>Download the Arduino .ino code from github and upload to the Master Arduino Interlocking Electronics module using the USB programmer.</li>
<li>Run the uploaded Android program to control the Red/Blue/Green LED.</li>
</ul>
<b>Parts list:</b>
<table border="2px solid">
<tr><th>Name</th><th>Description</th><th>Price</th></tr>
<tr><td>Master I2C Module</td><td>Interlocking Electronics Master I2C module: found at <a href="https://www.tindie.com/products/InterlockingElectronics/master-arduino/">https://www.tindie.com/products/InterlockingElectronics/master-arduino/</a></td><td>$15.00</td></tr>
<tr><td>Slave I2C Bluetooth Module</td><td>Interlocking Electronics Slave I2C BlueTooth module: found at: <a href="https://www.tindie.com/products/InterlockingElectronics/interlocking-bluetooth/">https://www.tindie.com/products/InterlockingElectronics/interlocking-bluetooth/</a></td><td>$25.00</td></tr>
<tr><td>Slave I2C RGB LED</td><td>Red/Green/Blue I2C LED found at: <a href="https://www.tindie.com/products/InterlockingElectronics/i2c-rgb-led/">https://www.tindie.com/products/InterlockingElectronics/i2c-rgb-led/</a></td><td>$12.00</td></tr>
<tr><td>USB Programmer</td><td>Interlocking Electronics Master USB Programmer: found at <a href="https://www.tindie.com/products/InterlockingElectronics/programmer/">https://www.tindie.com/products/InterlockingElectronics/programmer/</a></td><td>$10.00</td></tr>
<tr><td>Total</td><Td>&nbsp;</td><td>$62.00 + plus Android device</td></tr>
</table>
<H2>Let's get to it!</H2>
<hr>
<p>
<ol>
<li> The ADT Bundle containing Eclipse and the Android SDK can be found by following the download links provided on <a href="http://developer.android.com/sdk/index.html">http://developer.android.com/sdk/index.html</a>.  Unzip the .zip file to your computer.  I named mine C:\Android.  You will see an sdk and an eclipse directory.  The eclipse directory has eclipse.exe which is your IDE.  
</li>
<li>Install the windows drivers for your Android device.   I found the drivers for my Samsung Galaxy at <a href="http://developer.samsung.com/android/tools-sdks/Samsung-Andorid-USB-Driver-for-Windows">http://developer.samsung.com/android/tools-sdks/Samsung-Andorid-USB-Driver-for-Windows</a>. You may need to do a little digging.  I could not find drivers for my first choice (a cheap Walmart RCA Android) so I had to upgrade to the Samsung.  But I'm glad I did because I suspect the RCA Android tablet did not have bluetooth.<br>
Note: If you are using Windows 8 you may need to allow unsigned drivers (Advanced startup option)<br>
<b>To check if your driver is working.</b> 
<ul>
  <li>Connect your device to your computer</li>
  <li>Open a command window</li>
  <li>Navigate to your Android/sdk/platform-tools directory</li>
  <li>type: adb devices</li>
  <li>A device should show up on the list</li>
  <li>If it doesn't show up, try a different windows usb driver for your device</li>
</ul>
</li>

<li>Enable USB debugging on your Android device.  This is usually in the settings, developer options</li>
<li>Turn on Bluetooth.  This is in settings, Wireless and network.</li>
<li>Download the Android Elipse java project from github located at: <a href="https://github.com/Paulware/Tindie/tree/master/InterlockingElectronics/RGB">https://github.com/Paulware/Tindie/tree/master/InterlockingElectronics/RGB</a>. Extract the files to your Eclipse Android workspace directory.  Import the project to eclipse.  Run the program it will ask you for an android device.  Select your Android device for upload.</li>
<li>Download the Arduino .ino file from github also located at: <a href="https://github.com/Paulware/Tindie/tree/master/InterlockingElectronics/RGB">https://github.com/Paulware/Tindie/tree/master/InterlockingElectronics/RGB</a><br>
    In the Arduino IDE, select Tools, Board, Arduino Pro or Pro Mini (5V 16mhz) w/Atmega328.  Select the correct Com port.  Upload the .ino file to the Interlocking Electronics Master I2C module using the usb programmer.  The windows usb driver for the programmer is located <a href="http://www.silabs.com/Support%20Documents/Software/CP210x_VCP_Windows.zip">here</a>. 
<li>Run the BluetoothTest Android Program
   <ol>
   <li>Press "Search new Devices/Cancel" button</li>
   <li>Wait until HC-05 appears</li>
   <li>Select HC-05</li>
   <li>Wait until "Data Sent" appears</li>
   <li>Press "Red" "Green" "Blue" or "Off" button<br>
        The LED should respond accordingly
   </li>
   
   </ol>

</li>
</ol>
