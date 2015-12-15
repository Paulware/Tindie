<html>
<body>
<?php
include "common.inc";
include "common.php";

$user = getParam ("user");
$password = getParam ("password");


$sql = "Select * from Users where Username='$user'";
$result = query ( $sql);
if ($result) {
  echo "Sorry that username already exists."
}else {
  $sql = "UPDATE Users insert (UserName,Password) Values ('Pauly', 'Piper')";
  echo "$sql";
  $result = mysql_query($sql) or die("Could not execute: $sql");  
  echo "Success $user created<BR>"; 
}
?>
<br>
<input type="button" onclick=window.history.back();" value="back"><br>
</body>
</html>