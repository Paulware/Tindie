<html>
<body>
Creating tables<br>
<?php
  include "common.inc";
  include "common.php";
  
  function associate ( $p1, $p2) {
     $row = findProblem ($p1);
     $id1 = $row['ID'];
     $row = findProblem ($p2);
     $id2 = $row['ID'];
     $sql = "Insert Into Associations (ProblemId1, ProblemId2) Values ($id1, $id2)";
     $result = query ($sql);   
  }
  
  $q = mysql_query ("Drop Table Problems");
  $sql = "CREATE TABLE Problems (ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY, Name char(255), Description blob)";
  $result = query ($sql);
  $q = mysql_query ("Drop Table Solutions");
  $sql = "CREATE TABLE Solutions (ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY, ProblemId INT, Description blob)";
  $result = query ($sql);
  $q = mysql_query ("Drop Table Associations");
  $sql = "CREATE TABLE Associations (ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY, ProblemId1 INT, ProblemId2 INT)";
  $result = query ($sql);
  echo ("Tables created.");
  //*******   Done creating Tables   *******
  
  $description = 'Parents and children need an activity that combines the childs creativity/imagination with the parent knowledge/experience. <p>This site should be "read" by the parent and the child.  The child should choose which topics to focus on, and the parent should explain concepts or helps with the build.<p>The cost for each activity should be nominal.';
  $sql = "Insert Into Problems (Name,Description) Values ('IRBattleLab','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id();
  $description = '<img src=\"images/coatOfArms.jpg\" width=\"450px\"><hr><ul><li>Infra-Red describes the type of light emitted from the \"guns\".</li><li>Battle describes what the units will be doing on the field</li><li>Laboratory because we will be conducting experiments and learning basic electronics and physics and crafting the battle ground structures</li></ul>';  
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$description')";
  $result = query ($sql);
    
  $description = 'I need a way to \"fire\" on another unit';
  $sql = "Insert Into Problems (Name,Description) Values ('Infra-Red Basics','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $description = 'Infra-red beams fire \"information\" in the form of pulses at other units.<hr><img src=\"images/IRTxRx.jpg\"><hr>Long pulses and short pulses are interpretted as 1s and 0s.  Any data can be theoretically transmitted this way.'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$description')";
  $result = query ($sql);
 
  $description = 'I need a way to wire up an ir transmitter/receiver';
  $sql = "Insert Into Problems (Name,Description) Values ('IR Schematic','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $description = 'After some experimentation, it is clear that the digital outputs of the mini-pro microcontroller can be used as voltage source and ground for both the transmitter and the receiver<img src=\"images/MiniProTxRx.jpg\">'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$description')";
  $result = query ($sql);
  
  $description = 'Playing with only 2 tanks that never die can get boring after awhile. We need a more realistic game with different types of support units as well as attack units.<br>Also the battlefield itself should be more realistic.';
  $sql = "Insert Into Problems (Name,Description) Values ('Battle Strategy','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $solution = 'Using microcontrollers and infra-red technology we an create any type of static or mobile units. For example: <ul><li>Bazooka men</li><li>Helicopters</li><li>Fuel Depots</li><li>Ammo Depots</li><li>Mechanics</li></ul>';
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$solution')";
  $result = query ($sql);  
  
  $description = 'I need a way to \"refuel\" my vehicle before it runs out of fuel.'; 
  $sql = "Insert Into Problems (Name,Description) Values ('Fuel Depot','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $solution = 'I fuel depot can be made with an arduino mini-pro for less than $5, TODO: provide a link to an instructable to show how this can be accomplished.';
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$solution')";
  $result = query ($sql);  
  
  $description = 'I need a way to provide ammunition to my tank when it runs out';
  $sql = "Insert Into Problems (Name,Description) Values ('Ammo Depot','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $solution = 'An ammunitions depot can be made with an arduino mini-pro for less than $5, TODO: provide a link to an instructable to show how this can be accomplished';
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$solution')";
  $result = query ($sql);  
  
  $description = 'I need to add helicopters to the IR battlefield';
  $sql = "Insert Into Problems (Name,Description) Values ('Helicopters','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $solution = 'Jada Machines has a Helicopter that fires an infra-red pulse<br> <img src=\"images/jadaHelicopter.jpg\" width=\"450px\"><br>But the IR pulse will need to be read.'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$solution')";
  $result = query ($sql);  
  
  $description = 'I need to read and duplicate an IR pulse';
  $sql = "Insert Into Problems (Name,Description) Values ('Reading IRPulse','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $solution = 'A microcontroller will need to be used that will read the pulse every 50 microseconds and then count how long the pulse lasts.  Short pulses are viewed as 0 and long pulses are valued as a 1.  Different devices may have different lengths of pulses.'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$solution')";
  $result = query ($sql);    
  
  $description = 'I need to way to program a microcontroller';
  $sql = "Insert Into Problems (Name,Description) Values ('Microcontroller Programming','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $solution = 'There is a free Integrated Development Environment (IDE), available at <a href=\"https://www.arduino.cc/en/Main/Software\">https://www.arduino.cc/en/Main/Software</a> that can be used to program arduino (atmega) microcontroller'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$solution')";
  $result = query ($sql);    
  
  $description = 'I need a way to craft structures and terrain for the battle ground, with emphasis on cities';
  $sql = "Insert Into Problems (Name,Description) Values ('Crafting','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $solution = 'Using poster board, paint, styrofoam, cardboard, popsicle sticks and hot-glue we will construct terrain and buildings.'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$solution')";
  $result = query ($sql);  
  
  $description = 'I need a way to create buildings for my battleground';
  $sql = "Insert Into Problems (Name,Description) Values ('Buildings','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $solution = 'Using poster board or cardboard, you can create a bombed-out building<br><img src=\"images/bombedOutCardboard.jpg\" width=\"450px\">'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$solution')";
  $result = query ($sql);  
  
  $description = 'I need a way to create brick buildings for my battleground';
  $sql = "Insert Into Problems (Name,Description) Values ('Bricks','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $solution = 'Using poster board and paint, brick buildings can be created like this:<br> <img src=\"images/brickBuilding.jpg\" width=\"450px\"><br>First separate the paper from the foam board using hot water.  Here is a demonstration <a href=\"https://www.youtube.com/watch?v=6rR95WfP_uA&feature=iv&src_vid=45750YvPNHw&annotation_id=annotation_800659\">link</a>. <br> Next, create the brick building, here is a link to a good video on the subject:<a href=\"https://www.youtube.com/watch?v=03tIWjrcHK0\">https://www.youtube.com/watch?v=03tIWjrcHK0</a>'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$solution')";
  $result = query ($sql);  

  $description = 'I need to create a \"brain\" for my devices that will control the motors and the guns.';
  $sql = "Insert Into Problems (Name,Description) Values ('Microcontroller','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $description = 'Microcontrollers are like jellyfish <img src=\"images/jellyfish.jpg\">.  A jellyfish has many tentacles, which it can use to sense the presense of a small fish.  A microcontroller <img src=\"images/dip16.jpg\" width=\"150px\"> also has many data lines that can be used to read sensors or control electronic components';
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$description')";
  $result = query ($sql); 
 
  $description = 'I need to make terrain for my battlefield';
  $sql = "Insert Into Problems (Name,Description) Values ('Create Hills','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $description = '<br><img src=\"images/steppedHill.jpg\" width=\"450px\"><br>Here is a link to a good video on making hills:<a href=\"https://www.youtube.com/watch?v=_DsTFNU7-Rs">https://www.youtube.com/watch?v=_DsTFNU7-Rs</a>'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$description')";
  $result = query ($sql); 
  
  $description = 'I need to a way to \"repair\" my unit when it is \"destroyed\" on the battlefield.';
  $sql = "Insert Into Problems (Name,Description) Values ('Mechanic','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $description = 'A \"mechanic\" unit can be created that will \"reset\" a tank when it is close by.  The easiest way to create this unit is to have it \"fire\" a specific infra-red pulse that the tank will interpret as a \"repair\" signal.  The unit should be very vulnerable to attack (One shot would kill it).'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$description')";
  $result = query ($sql); 
  
  $description = 'I need to provide a way for a player to control units on the battlefield.';
  $sql = "Insert Into Problems (Name,Description) Values ('User Interface','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $description = 'A graphical user interface is a program which allows a person to interface with an electronic device.  The easiest to use interface that i have found is an application which runs on an android pohone.  A bluetooth-enabled, no-contract android phone is cheap, powerful, and can be purchased at best buy online for less than $30.<br>The free MIT App Inventor 2 <a href=\"http://ai2.appinventor.mit.edu\">http://ai2.appinventor.mit.edu</a> can be used to program these using a model based drag-and-drop interface.'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$description')";
  $result = query ($sql); 
  
  $description = 'I need make a round brick house for my battlefield.';
  $sql = "Insert Into Problems (Name,Description) Values ('Round House','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $description = 'Materials:<br><ul><li>Foam poster board from dollar tree</li><li>Red and Grey paint from Michaels($0.79 for 2 ounces)</li><li>Small sponge brush ($0.50)</li><li>Super glue and regular (white) glue ($2.00)</li></ul><img src=\"images/roundHouse.jpg\"> <br>First remove the paper from the foam board (hot water can be used, here is a <a href=\"https://www.youtube.com/watch?v=6rR95WfP_uA&feature=iv&src_vid=45750YvPNHw&annotation_id=annotation_800659\">link</a>).<br>Next, draw and paint the bricks, here is a detailed link: <a href=\"https://www.youtube.com/watch?v=45750YvPNHw\">https://www.youtube.com/watch?v=45750YvPNHw</a>'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$description')";
  $result = query ($sql); 
  
 
  $description = 'I need make other types of hills for the battlefield.';
  $sql = "Insert Into Problems (Name,Description) Values ('Cork Hills','$description')";
  $result = query ($sql);  
  $problemId = mysql_insert_id(); 
  $description = 'An excellent video is here on how to make a cork hill: <a href=\"https://www.youtube.com/watch?v=sOy5yqctzzA\">https://www.youtube.com/watch?v=sOy5yqctzzA</a>'; 
  $sql = "Insert Into Solutions (ProblemId, Description) Values ($problemId,'$description')";
  $result = query ($sql); 

  associate ('IR Schematic', 'Microcontroller');
  associate ('Buildings', 'Bricks');
  associate ('Buildings', 'Create Hills');
  associate ('Crafting', 'Buildings');
  associate ('Crafting', 'Create Hills');
  associate ('Crafting', 'Round House');
  associate ('Crafting', 'Cork Hills');
  associate ('Buildings', 'Crafting');
  associate ('Create Hills', 'Crafting');
  associate ('Round House', 'Crafting');
  associate ('Cork Hills', 'Crafting');
  associate ('Bricks', 'Crafting');
  associate ('Microcontroller', 'Microcontroller Programming');
  associate ('Reading IRPulse', 'Microcontroller Programming');
  associate ('Helicopters', 'Reading IRPulse');
  associate ('Battle Strategy', 'Helicopters');
  associate ('Battle Strategy', 'Ammo Depot');
  associate ('Battle Strategy', 'Fuel Depot');
  associate ('Battle Strategy', 'Create Hills');
  associate ('Battle Strategy', 'Mechanic');
  associate ('Infra-Red Basics', 'IR Schematic');
  associate ('IR Schematic', 'Infra-Red Basics');   
  associate ('IRBattleLab', 'Crafting');
  associate ('IRBattleLab', 'Battle Strategy');
  associate ('IRBattleLab', 'Infra-Red Basics');
  associate ('IRBattleLab', 'User Interface');  
  associate ('Mechanic', 'Infra-Red Basics');
  associate ('Mechanic', 'IR Schematic');
  associate ('Mechanic', 'Microcontroller Programming');
  
?>
</body>
</html>