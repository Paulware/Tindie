<?php
  include "common.inc";
  include "common.php";
  
  $MAC = getParam ("MAC");
  $User = getParam ("User");
  echo ("MAC: $MAC, User: $User<br>\n");
  $sensorRow = findSensor($MAC);
  $sensorId = $sensorRow['ID'];
  echo ( "sensorId: $sensorId<br>\n");
  $userRow = findUser ($User);
  $userId = $userRow['ID'];
  echo ( "userId: $userId<br>\n");
?>

<html>
<head><Title>Delete Sensor</Title>

</head>

<body>

<?php

  echo ("mac address: $MAC<br>\n");
  if (!$sensorRow) {
     echo ( "Could not find sensor with mac address: $MAC<br>\n");
  } else if (!$userRow) { 
    echo ( "Could not find user with name: $User<br>\n");
  } else {
     $sql = "Delete From Sensors Where MAC ='$MAC'";
     echo ("$sql<br>\n");
     query ($sql);
     $sql = "Delete From Owners Where User=$userId and Sensor=$sensorId";
     echo ("$sql<br>\n");
     query ($sql);
     echo ( "$User no longer associated with sensor: $MAC\n");  
     echo ("<Script>\n");
     echo ("  window.location.href = 'index.php';\n");
     echo ( "</Script>\n");     
  }
?>
</body>
</html>