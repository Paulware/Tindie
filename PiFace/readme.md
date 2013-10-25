Welcome to the documentation for the apache-piFace sd card
<p>
Here are some unix basic:
<ul>
  <li>To list the files in a directory use the command: ls </li>
  <li>To edit a file use the command: sudo nano filename</li>
  <li>To change directories use the command: cd directory</li>
  <li>To delete a file use the command: sudo rm filename</li>
  <li>To copy a file use the command: sudo cp filename newpathlocation</li>
  <li>To rename a file use the command: sudo mv filename newName</li>
  <li>When a cgi file is created use this command to make it executable: sudo chmod +x filename </li>
</ul>


Here are some pi basics:
<ul>
  <li>When the pi boots up it will send you an email saying what ip address it is at.  This is a useful backup/alternate to no-ip.com</li>
  <li>To see your web-page from outside you will need to configure your router to port-forward port 80 from your raspberry pi.</li>  
  <li>To transfer a file from windows to the pi, you can insert the sd card into your pc and copy the file to the /boot directory.  When you place the sd card in the pi you will be able to access the file</li>
  <li>The pi is configured to run headless (without screen).  You will need the free vnc viewer from <a href="http://www.tightvnc.com/download.php">here</a></li>
  <li>To login via ssh, you can use the free windows application: putty.  The username is pi and password is raspberry</li>
  <li>To change the password for ssh, use: sudo raspi-config and select "change user password"</li> 
  <li>Files can be transferred between pc and raspberry pi using winscp: <a href="http://winscp.net/eng/index.php">http://winscp.net/eng/index.php</a></li>
  <li>Alternately you can read/write to the /boot directory from your laptop by placing the sd card in a usb reader or slot</li>
</ul>

Here are some web-page basics:
<ul>
  <li>The default web-page is located at: /var/www</li>
  <li>The cgi files are located at: /usr/lib/cgi-bin</li>
  <li>Javascript is used to call invoke the cgi-bin files</li>
  <li>You can create a button like use: input type=button onclick="jfunction()" value="text" </li>
  <li>Use this javascript command to invoke a cgi-bin file: document.location="cgi-bin/filename.cgi";</li>
</ul>

Here are some pi-face basics:
<ul>
  <li>Excellent online tutorial: <a href="http://www.startpi.co.uk/getting-started-with-pi-face.html">http://www.startpi.co.uk/getting-started-with-pi-face.html</a></li>
</ul>


<b>Configuration</b><br>
<ul>
<li>Set your email address and password</li>
   <ul>
      <li>Create a gmail account if you don't have one already</li>
      <li>Modify the file: MyMail.py located: /home/pi/python_udp/MyMail.py</li>
   </ul>
</ul>

Here is a useful tutorial on using piface: <a href="http://raspberrywebserver.com/gpio/piface/building-a-remote-control-vehicle-using-a-raspberry-pi.html#.UkpHsUAo7tQ">http://raspberrywebserver.com/gpio/piface/building-a-remote-control-vehicle-using-a-raspberry-pi.html#.UkpHsUAo7tQ</a>