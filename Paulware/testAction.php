<?php
  include "common.inc";
  include "common.php";
  $MACOn = getParam ("MACOn");
  $MACOff = getParam ("MACOff");
  $Sensor = getParam ("Sensor");
  $Action = getParam ("Action");
  $Event = getParam ( "Event");
  $Phone = getParam ("Phone");
  $Username = getParam ("Username");
  $Message = getParam ("Message");
  $Subject = getParam ("Subject");
  $Body = getParam ("Body");
  $Provider = getParam ("Provider");
  $TriggerValue = getParam ("TriggerValue");
  
?>

<html>
<head> <Title>Test Sensor Action</Title>
</head>
<body>
<?php
  function sendEmail ($recipient, $subject, $body) {
     $message = "$recipient`$subject`$body";
     $command = "python sendMail.py \"$recipient\" \"$subject\" \"$body\"";   
     echo ( "<h1>CMD:</h1><br>$command<BR>\n");

     error_reporting(E_ALL);

     /* Add redirection so we can get stderr. */
     $handle = popen($command, 'r');
     echo "'$handle'; " . gettype($handle) . "\n";
     $read = fread($handle, 2096);
     echo $read;
     pclose($handle);   
  }

  echo ( "MACOn: $MACOn MACOff: $MACOff Sensor:$Sensor Action:$Action Event:$Event Phone:$Phone Username:$Username Message:$Message Subject:$Subject Body:$Body TriggerValue:$TriggerValue");
  if ($Action == 'email') {
     sendEmail ($Username, $Subject, $Body);
  } else if ($Action == 'text') {
     if ($Provider=="alltel") {
        $Username="$Phone@message.alltel.com";
     } else if ($Provider=="att") {
        $Username="$Phone@txt.att.net";
     } else if ($Provider=="boost") {
        $Username="$Phone@myboostmobile.com";   
     } else if ($Provider=="cricket") {
        $Username="$Phone@sms.mycricket.com";   
     } else if ($Provider=="metro") {
        $Username="$Phone@mymetropcs.com";   
     } else if ($Provider=="nextel") {
        $Username="$Phone@messaging.nextel.com";   
     } else if ($Provider=="qwest") {
        $Username="$Phone@qwestmp.com";   
     } else if ($Provider=="tmobile") {
        $Username="$Phone@tmomail.net";   
     } else if ($Provider=="sprintpcs") {
        $Username="$Phone@messaging.sprintpcs.com";   
     } else if ($Provider == "sprintpm") {
        $Username="$Phone@pm.sprint.com";
     } else if ($Provider=="suncom") {
        $Username="$Phone@tms.suncom.com";   
     } else if ($Provider=="uscellular") {
        $Username="$Phone@email.uscc.net";   
     } else if ($Provider=="verizon") {
        $Username="$Phone@vtext.com";   
     } else if ($Provider=="virgin") {
        $Username="$Phone@vmobl.com";   
     }
     
     sendEmail ($Username, '', $Message);     
  }
?>

<Script>  
</Script>
</Body>
</html>