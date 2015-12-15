<html>
<body>
<?php
include "common.inc";
include "common.php";

$mac = getParam ("MAC");
$value = getParam ("value");

$sql = "UPDATE Sensors SET value='$value' WHERE MAC='$mac'";
echo "$sql";

$result = mysql_query($sql) or die("Could not execute: $sql");  

$sql = "UPDATE Sensors SET Timestamp=CURRENT_TIMESTAMP WHERE MAC='$mac'";
echo "$sql";
$result = mysql_query($sql) or die("Could not execute: $sql");  
echo "Success $mac=$value<BR>"; 
?>
</body>
</html>