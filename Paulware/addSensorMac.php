<?php
  include "common.inc";
  include "common.php";
  
  $user = $_COOKIE["user"]; 
  $mac = getParam ("mac");
  $sensorType=getParam("sensorType");
  $sensorRow = findSensor($mac);
?>

<html>
<head> <Title>Add Sensor</Title>

</head>

<body>

<?php
  echo ("mac address: $mac<br>\n");
  echo ("sensor type: $sensorType<br>\n");
  if ($sensorRow) {
     echo ( "That sensor already exists!");
  } else {
     $sql = "Insert into Sensors (MAC, Value,TypeName) values ( '$mac','0','$sensorType')";
     echo ("$sql<br>\n");
     query ($sql);
     echo ( "That sensor does not yet exist, added it to the Sensors Table");  
  }
  $result = findUser ($user);
  $userId = 0;
  if ($result) {
     $userId = $result["ID"];
  } 
  $sensorId = 0;
  $result = findSensor ($mac);
  if ($result) {
    $sensorId = $result["ID"];
  }
  echo ( "Add user $userId/Sensor $sensorId to Owners table");  
  $match= findMatch ($userId,$sensorId);
  
  if (!$match) {
    $sql = "Insert into Owners (Sensor,User) values ( '$sensorId','$userId')";
    echo ("$sql<br>\n");
    query ($sql);
    echo ( "User $userId and sensor $sensorId added to Owners\n");          
  } else {
    echo ("Already find a match with $userId and $sensorId");    
  }
  echo ("<Script>\n");
  echo ("  window.location.href = 'index.php';\n");
  echo ( "</Script>\n");     
?>
</body>
</html>