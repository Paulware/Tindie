<html>
<body>
<?php
$output = array();
exec("python sendMail.py", $output);
var_dump( $output);
?>
<p>
   Email sent
</body>
</html>