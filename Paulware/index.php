<html>
<head>
<title>Home Automation http://PaulwareSensorGroup.ddns.net/Paulware</title>
<Script>
  <?php
  $user = $_COOKIE["user"]; 
  echo ( "   var User='$user';\n")
  ?>
  function modifyNickname(MAC,Nickname) {
     window.location.href = 'updateNickname.php?Nickname=' + Nickname + '&MAC=' + MAC;     
  }
  function deleteSensor(MAC) {
     window.location.href = 'deleteOwner.php?User=' + User + '&MAC=' + MAC;     
  }
  function changeAction(MAC) {
     window.location.href = 'editSensorAction.php?MAC=' + MAC;
  }
</Script>
</head>
<body>
<p><center style="font-size:200%">Welcome to Paulware Home Automation Center<br><a href="http://PaulwareSensorGroup.ddns.net/Paulware">http://PaulwareSensorGroup.ddns.net/Paulware</a></center></p>
<hr>
<h1><a href="store.php">Store</a></h1>
<hr>
<?php
  
  if ($user == "") {
     print ("<H1>Logged in as guest</H1><br>\n"); 
     print ("<input type=\"button\" value=\"Login/Create an account\" onclick=\"location.href='login.php';\"><br>\n");
     print ("<hr><p><H1>View sensors</H1>\n" );
  } else {
     print ("<H1>Welcome $user</H1><br>\n"); 
     print ("<input type=\"button\" value=\"Logout\" onclick=\"location.href='logout.php';\"><br>\n");
     print ("<input type=\"button\" value=\"Add Sensor\" onclick=\"location.href='addSensor.php';\"><br>\n");
     print ("<hr><p><H1>View and control sensors</H1>\n" );
  }
  
?>
<table border="2px solid">
<?php
   include "common.inc";
   include "common.php";
   if ($user=="") {
       echo ("<tr><th>MAC</th><th>Value</th><th>Timestamp</th></tr>\n");
       $result = query ( "Select * From Sensors" );
       while ($row = mysql_fetch_assoc ($result)) 
       {		 
         $MAC = $row["MAC"];
         $Value = $row["Value"];
         $Timestamp = $row["Timestamp"];
         $Location = $row["Nickname"];
         print ("<tr><td>$MAC</td><td>$Value</td><td>$Timestamp</td></tr>");
       }
    
   } else if ($user=="Paulware"){
?>
<h1>Things to do </h1>
<hr>
<ul>
<li>Modify Sensor Types<input type="checkbox"></li>
<li>Output based on sensor type<input type="checkbox"></li>
<li>Sensor values trigger email<input type="checkbox"></li>
<?php
       echo ("<tr><th>Type</th><th>MAC</th><th>Value</th><th>Timestamp</th><th>Delete</th><th>Location</th><th>Action</th></tr>\n");
       $result = query ( "Select * From Sensors" );
       $count = 0;
       while ($row = mysql_fetch_assoc ($result)) 
       {		 
         $TypeName = $row["TypeName"];
         $MAC = $row["MAC"];
         $Value = $row["Value"];
         $Timestamp = $row["Timestamp"];
         $Location = $row["Nickname"];
         print ("<tr><td>$TypeName</td><td>$MAC</td><td>$Value</td><td>$Timestamp</td><td><input type=\"button\" value=\"Delete\" onclick=\"deleteSensor('$MAC');\"></td><td><input name=\"location$count\" value=\"$Location\" onchange=\"modifyNickname('$MAC',this.value);\"></td><td><input onclick=\"changeAction('$MAC');\" type=\"button\" value=\"Modify Action\"></td></tr>");
         $count = $count + 1;
       }
    
   } else {
     echo ("<tr><th>MAC</th><th>Value</th><th>Timestamp</th><th>Delete</th><th>Location</th></tr>\n");
     $id = findUser($user);
     if ($id) {
       $userId = $id['ID'];
       $sql = "Select * From Owners Where User=$userId";

       $result = query ( "Select * From Owners Where User=$userId" );
       $count=0;
       while ($row = mysql_fetch_assoc ($result)) 
       {		 
         $sensorId = $row['Sensor'];
         $sensor = findSensorId ($sensorId);

         $MAC = $sensor["MAC"];
         $Value = $sensor["Value"];
         $Timestamp = $sensor["Timestamp"];
         $Location = $sensor["Nickname"];
         print ("<tr><td>$MAC</td><td>$Value</td><td>$Timestamp</td><td><input type=\"button\" value=\"Delete\" onclick=\"deleteSensor('$MAC');\"><td><input name=\"location$count\" value=\"$Location\" onchange=\"modifyNickname('$MAC',this.value);\"></td></tr>");
         $count = $count + 1; 
       }
     }    
   }    
?>
</table>
<hr>
Support/Webmaster: paulware@hotmail.com
</body>
</html>
