<?php
  include "common.inc";
  include "common.php";
  
  $MAC = getParam ("MAC");
  $Nickname = getParam ("Nickname");
  
?>

<html>
<head><Title>Update Nickname</Title>

</head>

<body>

<?php
  //sendHi();
  $sql = "Update Sensors set Nickname='$Nickname' where MAC='$MAC'";
  echo ("$sql<br>\n");
  query ($sql);
  echo ( "Nickname updated<br>");  
  echo ("<Script>\n");
  echo ("  window.location.href = 'index.php';\n");
  echo ( "</Script>\n");     
?>
</body>
</html>