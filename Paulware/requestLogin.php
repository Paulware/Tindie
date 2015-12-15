<?php
  include "common.inc";
  include "common.php";
  $user = getParam ("user");
  $password = getParam("password");
?>

<html>
<head> <Title>Checking Login</Title>
</head>
<body>
<?php
  $row = findUser($user);
  if ($row) {
    $pword = $row['Password'];
    if ($pword == $password) {
       echo ("$user now logged in, set the cookie");
       setcookie ("user", "$user", time()+36000);
       echo ("<Script>window.location.href = 'index.php';</Script>\n");       
    } else {
       echo ("<h1>Bad password please go back and try again.</h1><hr>");
    }    
  } else {   
    $sql = "Insert into Users (Username,Password) values ( '$user','$password')"; 
    echo $sql + "<br>\n";
    query ($sql);
    echo ( "$user added to the Users table"); 
    setcookie ("user", "$user", time()+36000);
    echo ("<Script>window.location.href = 'index.php';</Script>\n");
  }
?>
</body>
</html>