<html>
<body>
Creating tables<br>
<?php 
  include "common.inc";
  include "common.php";
  $q = mysql_query ("Drop Table Sensors");
  $sql = "CREATE TABLE Sensors (ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY, MAC char(255), Value char(255), Nickname char(255), Timestamp datetime default CURRENT_TIMESTAMP, TypeName char(255), Action INT)";
  $result = query ($sql);
  $q = mysql_query ("Drop Table Users");
  $sql = "CREATE TABLE Users (ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY, Username char(255), Password char(255))";
  $result = query ($sql);
  $q = mysql_query ("Drop Table Owners");
  $sql = "CREATE TABLE Owners (ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY, User INT NOT NULL, Sensor INT NOT NULL)";
  $result = query ($sql);
  $q = mysql_query ("Drop Table Actions");
  $sql = "CREATE TABLE Actions (ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY, Sensor INT NOT NULL, Action char(255), Event char(255), MAC char(255), Phone char(255), Username char(255), Message char(255), Subject char(255), Body char(1024), Provider char(255), AffectedMAC char(255))";
  $result = query ($sql);
  echo ("Tables created.");
?>
</body>
</html>