<?php
  $user = $_COOKIE["user"]; 
?>

<html>
<head> <Title>Add Sensor</Title>

<script>
  <?php
     print ( '  var user=\'$user\';');
  ?>
  function addSensor (value, sensorType) {
    window.location.href = 'addSensorMac.php?mac=' + value + '&sensorType=' + sensorType;
  }

</script>

</head>

<body>
Sensor's MAC Address:<input name="macAddress"><br>
Sensor Type: <Select name="sensorType">
<option value="temperature">Temperature</option>
<option value="motionSensor">Motion Sensor</option>
<option value="waterSensor">Water Sensor</option>
</Select>
<br>
<input type=button value="Add" onclick="javascript:addSensor(document.all.macAddress.value, document.all.sensorType.value);">
</body>
</html>