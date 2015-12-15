<?php

   function sendHi () {
     sendEmail ( 'Hello', 'What is up?');
   }
   
   function sendElectronicMail ($subject, $message) {
     $name = 'Paul Richards'; // $_POST['name'];
     $email = 'richardspaulr1@gmail.com';
     //$message = $_POST['message'];
     $from = 'richardspaulr1@gmail.com'; 
     $to = 'Paulware@hotmail.com';
     // $subject = 'Customer Inquiry';
     $body = "From: $name\n E-Mail: $email\n Message:\n $message";

     //if ($_POST['submit']) {
         if (mail ($to, $subject, $body, $from)) { 
             echo '<p>Your message has been sent!</p>';
         } else { 
             echo '<p>Something went wrong, go back and try again!</p>'; 
         }
     //}
   }   
   function query ( $sql ) {
     $q = mysql_query ($sql) or die ("Could not execute: $sql");
     return $q;  
   }  
   
   function findSensor($mac) {
     $sql = "Select * From Sensors Where MAC='$mac'";
     $result = query ( $sql);
     return mysql_fetch_assoc($result);          
   }
  
   function findSensorId($id) {
     $sql = "Select * From Sensors Where ID=$id";
     $result = query ( $sql);
     return mysql_fetch_assoc($result);          
   }
     
   function findMatch($user, $sensor) {
     $sql = "Select * From Owners Where User='$user' and Sensor='$sensor'";
     $result = query ( $sql);
     return mysql_fetch_assoc($result);              
   }   
   
   function getParam ($name) {
      $value = $_GET["$name"];
      if ($value == "")
        $value = $_REQUEST["$name"];
       return $value;      
   }
   
   // Get lines ready for display
   function unescapeCharacters ($line) {
     $line = str_replace ('&#060;','<',$line);
     $line = str_replace ('&#062;','>',$line);
     $line = str_replace ('&#146;','\'',$line);
     $line = str_replace ('&#147;','"',$line);
	    $line = str_replace ('\r\n','<BR>',$line);
     //$line = str_replace ('&','$2$1$', $line);	 
	    $line = str_replace ('&#092;','\\',$line);
	    return $line;
   }
   
   function escapeCharacters ( $line ) {
     $line = str_replace ('<','&#060;',$line);
     $line = str_replace ('>','&#062;',$line);
     $line = str_replace ('\'','&#146;',$line);
     $line = str_replace ('"','&#147;',$line);
	    $line = str_replace ('\\','&#092;',$line);
     //$line = str_replace ('\r\n', '<BR>', $line );
     // Do not escape <BR>, <LI>, <UL>, or <OL> or others
     $line = str_replace ('&#060;BR&#062;','<BR>',$line );
     $line = str_replace ('&#060;LI&#062;','<LI>',$line );
     $line = str_replace ('&#060;UL&#062;','<UL>',$line );
     $line = str_replace ('&#060;OL&#062;','<OL>',$line );
     $line = str_replace ('&#060;/LI&#062;','</LI>',$line );
     $line = str_replace ('&#060;/UL&#062;','</UL>',$line );
     $line = str_replace ('&#060;/OL&#062;','</OL>',$line );
     $line = str_replace ('&#060;br&#062;','<br>',$line );
     $line = str_replace ('&#060;li&#062;','<li>',$line );
     $line = str_replace ('&#060;ul&#062;','<ul>',$line );
     $line = str_replace ('&#060;ol&#062;','<ol>',$line );
     $line = str_replace ('&#060;/li&#062;','</li>',$line );
     $line = str_replace ('&#060;/ul&#062;','</ul>',$line );
     $line = str_replace ('&#060;/ol&#062;','</ol>',$line );
     $line = str_replace ('&#060;b&#062;','<b>',$line );
     $line = str_replace ('&#060;/b&#062;','</b>',$line );
     $line = str_replace ('&#060;B&#062;','<B>',$line );
     $line = str_replace ('&#060;/B&#062;','</B>',$line );
	    $line = str_replace ('&#092;','\\',$line );

     return $line;
   }

   function findUser($name) {
     $sql = "Select * From Users Where Username='$name'";
     $result = query ( $sql);
     return mysql_fetch_assoc($result);              
   }

?>