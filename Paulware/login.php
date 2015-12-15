<?php
  $user = '';
  $cookie_name = 'user';
  if(isset($_COOKIE[$cookie_name])) {
    echo "Cookie '" . $cookie_name . "' is set!<br>";
    echo "Value is: " . $_COOKIE[$cookie_name];
	$user = $_COOKIE[$cookie_name];
  }
  if ($user != "") 
  {
    setcookie ("user", "$user", time()+36000);
    header( 'Location: index.php' );
  }
?>

<html>
<head> <Title>Login Please</Title>

<script>


  function login (value) {
    var user = document.all.user.value;
    var password = document.all.password.value;
    window.location.href = 'requestLogin.php?user=' + user + '&password=' + password;
  }

</script>

</head>

<body>
If you don't have an account, one will be created for you automatically.
<table>
<tr><td>User Name</td><td><input name="user"></td></tr>
<tr><td>Password</td><td><input type="password" name="password"></td></tr>
</table><hr>
<input type=button value="Login" onclick="javascript:login(document.all.user.value);">
</body>
</html>