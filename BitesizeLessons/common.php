<?php

  function findProblem ( $name) {
    $sql = "Select * From Problems where Name='$name'";
    $result = query ( $sql );
    $row = mysql_fetch_assoc ($result);
    if (!$row) {
       echo ("Could not find problem name: $name<br>\n");
    }
    return $row;
  }
  
  function findProblemId ($id) {
    $sql = "Select * From Problems where Id=$id";
    $result = query ( $sql );
    $row = mysql_fetch_assoc ($result);
    return $row;
  }
  
  function findSolution ($problemName) {
    $row = findProblem ($problemName);
    $solutionId = $row['ID'];
    $sql = "Select * From Solutions where ID=$solutionId";
    $result = query ($sql);
    $row = mysql_fetch_assoc ($result);
    return $row;
  }

  function showFooter($filename) {
    echo ("<br><img src=\"images/$filename\" width=\"400px\">");
    echo ("<p>\n");
    echo ("<i>If you keep students motivated and having fun, there is no way they can avoid learning the technical details.</i>\n");
    echo ("<br>\n");
    echo ("Webmaster: paulware@hotmail.com");       
  }
  
  function problemFooter($id) {
    echo ("<hr>\n<input type=\"button\" value=\"Solution\" onclick=\"window.location.href='showSolution.php?id=$id';\">");    
    showFooter('brainPower.jpg');
  }
  
  function showProblemId ( $id) {
    $row = findProblemId ($id);
    $problemName = $row ['Name'];
    $title = $row['Name'];
    echo ("<h1>$title</h1>");
    echo ($row['Description']); 
    $solution = findSolution ($problemName);
    $id = $solution['ID'];
    problemFooter($id);
  }
  
  function showProblem ( $problemName) {
    $row = findProblem ($problemName);
    $title = $row['Name'];
    echo ("<h1>$title</h1>");
    echo ($row['Description']); 
    $solution = findSolution ($problemName);
    $id = $solution['ID'];
    problemFooter ($id);
  }
  
  function showSolution ( $solutionId) {
    $sql = "Select * From Solutions where ID=$solutionId";
    $result = query ($sql);
    $row = mysql_fetch_assoc ($result);
    $problemId = $row ['ProblemId'];
      
    echo ("<h1>Solution</h1>");
    echo ($row['Description']); 
    //echo ("<hr>\n<input type=\"button\" value=\"Solution\" onclick=\"window.location.href='showSolution.php?name=$id';\">");    
    
    $sql = "Select * from Associations Where ProblemId1 = $problemId";    
    $result = query ( $sql );
    echo ( "<hr><h1>Where should we go next?</h1><ul>");
    while ($row = mysql_fetch_assoc ($result)) {
       $id2 = $row['ProblemId2'];
       $sql = "Select * from Problems where Id=$id2";       
       $p = query ($sql);
       $problemInfo = mysql_fetch_assoc($p);
       if ($problemInfo) {
          $n = $problemInfo['Name'];     
          echo ( "<li><a href=\"showProblem.php?id=$id2\">$n</a></li>");
       } else { 
          echo ( "<li>Could not find problem: $id2</li>");
       }   
    }   
    echo ("</ul><br>\n");
    showFooter ( 'solution.jpg');
  }
  

  function insertSolution ( $problemName, $description ) {
    $row = findProblem ($problemName);
    $problemId = $row["ID"];
    if ($row)
    {
      $sql = "Insert into Solutions (ProblemId,description) Values ($problemId,$description)";
      $result = query ( $sql );
      echo ( "$description inserted for problem: $problemId");
    }
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