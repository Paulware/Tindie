More 8x8 icons are found <a href="http://graphicriver.net/item/nano-icons-8x8/4453769">here</a>
matrixMaster contains a sketch that allows a master IIC device to write to the 8x8 matrix 
  The master write 8 rows of data to the slave
matrixSlave contains the sketch that is loaded into the slave device 
  The slave reads the data using the Wire library and sets the leds appropriately.