More 8x8 icons are found <a href="http://graphicriver.net/item/nano-icons-8x8/4453769">here</a>
<br>
<ul>
<li>matrixMaster contains a sketch that allows a master IIC device to write to the 8x8 matrix <br>
  The master writes 8 rows of data to the slave.  Each row is 1 byte in size.</li>
<li>matrixSlave contains the sketch that is loaded into the slave device<br> 
  The slave reads the data using the Wire library and sets the leds appropriately.
  You will not need to change the slave code, unless you want the device to be stand alone  </li>
</ul>