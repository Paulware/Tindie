<?php
  include "common.inc";
  include "common.php";
  $MAC = getParam ("MAC");
  $Sensor = findSensor($MAC)['ID'];
?>

<html>
<head> <Title>Edit Sensor Action</Title>
</head>
<body>
<?php
  echo ( "<center><H1>$MAC</H1></center><BR>");
?>

When 
<Select name="Event" onchange="changeEvent();">
<option value="motion">Motion Detected</option>
<option value="colder">Temperature Below</option>
<option value="warmer">Temperature Above</option>
<option value="water">Water Detected</option>
</Select>
<div id="divTrigger" style="display:none;"><input name="TriggerValue"> degrees Fahrenheit</div>
<Select name="Action" onchange="changeSelection();">
<option value="email">Send an Email</option>
<option value="text">Send a text</option>
<option value="on">Turn on a device</option>
<option value="off">Turn off a device</option>
<option value="photo">Send a photo(TBD)</option>
</Select>

<div id="divEmail">
To:<input name="Username"><br>
Subject: <input name="Subject"><br>
Body: <input name="Body"><br>
</div>

<div id="divPhoto" style="display:none;">
To:<input name="PhotoUsername"><br>
Subject: <input name="PhotoSubject"><br>
Trigger Device: <input name="PhotoDevice"><br>
</div>

<div id="divText" style="display:none;">
Provider: <Select name="Provider">
<option value="alltel">Alltel</option>
<option value="att">AT&T</option>
<option value="boost">Boost Mobile</option>
<option value="cricket">Cricket</option>
<option value="metro">Metro PCS</option>
<option value="nextel">Nextel</option>
<option value="qwest">Qwest</option>
<option value="tmobile">T-Mobile</option>
<option value="sprintpcs">Sprint PCS</option>
<option value="sprintpm">Sprint PM</option>
<option value="suncom">suncom</option>
<option value="uscellular">US Cellular</option>
<option value="verizon">Verizon</option>
<option value="virgin">Virgin Mobile</option>
</Select>
Phone Number: <input name="Phone"><br>
Message: <input name="Message" size="60"><br>

</div>
<div id="divOn" style="display:none;">
Turn on a device<br>
MAC: <input name="MACOn"><br>
</div>
<div id="divOff" style="display:none;">
Turn off a device<br>
MAC: <input name="MACOff"><br>
</div>

<Script>
  <?php
  echo ("   var Sensor = $Sensor;\n" );
  ?>
  var Action;
  var Event;
  var Phone;
  var Username;
  var Message;
  var Subject;
  var Body;
  var Provider;
  var MACOn;
  var MACOff;
  var TriggerValue;
  var PhotoUsername;
  var PhotoSubject;
  var PhotoDevice;
  
  function getVariables() {
     Action=document.all.Action.value;   
     Event=document.all.Event.value;
     Phone=document.all.Phone.value;
     Username=document.all.Username.value;
     Message=escape(document.all.Message.value);
     Subject=escape(document.all.Subject.value);
     Body=escape(document.all.Body.value);
     Provider=document.all.Provider.value;
     MACOn=document.all.MACOn.value;
     MACOff=document.all.MACOff.value;
     TriggerValue=document.all.TriggerValue.value;
     if (Action=='photo') {
        Username = document.all.PhotoUsername.value;
        Subject = document.all.PhotoSubject.value;
        MACOn = document.all.PhotoDevice.value;
        Body = "Photo triggered by " + MACOn;
        Action = 'email';
     }   
  }
  
  function addAction () {   
     getVariables();
     alert ( 'window.location.href = \'addAction.php?Sensor=' + Sensor + '&Action=' + Action + '&Event=' + Event + 
             '&Phone=' + Phone + '&Username=' + Username + '&Message=' + Message + '&Subject=' + Subject + '&Body' + 
             Body + '&Provider=' + Provider + '&MACon=' + MACOn + '&MACOff=' + MACOff + '&TriggerValue=' + TriggerValue);             
  }
  function testAction () {
     getVariables();
     window.location.href = 'testAction.php?Sensor=' + Sensor + '&Action=' + Action + '&Event=' + Event + 
             '&Phone=' + Phone + '&Username=' + Username + '&Message=' + Message + '&Subject=' + Subject + '&Body=' + 
             Body + '&Provider=' + Provider + '&MACOn=' + MACOn + '&MACOff=' + MACOff + '&TriggerValue=' + TriggerValue;             
  }
  function deleteAction() {
     alert ( 'Delete an action');
  }
  function showTemp() {
     document.all.divTrigger.style.display = 'none';
     if (document.all.Event.value == 'warmer') {
        document.all.divTrigger.style.display = 'block';     
     } else if (document.all.Event.value == 'colder') {
        document.all.divTrigger.style.display = 'block';
     }      
  }
  function changeEvent() {
     showTemp();
  }
  function changeSelection() {
     document.all.divText.style.display    = 'none';
     document.all.divEmail.style.display   = 'none';
     document.all.divOn.style.display      = 'none';
     document.all.divOff.style.display     = 'none';
     
     if (document.all.Action.value == 'email') {
        document.all.divEmail.style.display = 'block';
     } else if (document.all.Action.value == 'text') {
        document.all.divText.style.display = 'block';
     } else if (document.all.Action.value == 'on') {
        document.all.divOn.style.display = 'block';      
     } else if (document.all.Action.value == 'off') {
        document.all.divOff.style.display = 'block';     
     } else if (document.all.Action.value=='photo') {      
        document.all.divPhoto.style.display='block';
     }
     showTemp();
  }
</Script>
<?php
  $row = findSensor($MAC);
  if ($row) {   
    $sensorId = $row['ID'];
    $count = 0;
    $result = query ( "Select * From Actions Where Sensor = $sensorId" );
    while ($row = mysql_fetch_assoc ($result)) 
    {		         
      if ($count == 0) {
        echo ("<Table Border=\"2\">");    
        echo ("<tr><th>Count</th><th>Action</th><th>Delete</th></tr>\n");
      }
      $count = $count + 1;
      $action = $row["Action"];
      if ($count == 1) {
         echo ( "<tr><td>$count</td><td>$action</td><td><input type=\"button\" value=\"Delete\" onclick=\"deleteAction();\"></tr>");    
      }
    }
    echo ("</Table>");    
    // echo ("<Script>window.location.href = 'index.php';</Script>\n");               
  } 
?>
<input type="button" value="Add Action" onclick="addAction();">
<br>
<input type="button" value="Test" onclick="testAction();">
</body>
</html>