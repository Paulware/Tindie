<html>
<head>
<base target="_self">
</head>

<!--
    Use the "onload" event to start the refresh process.
-->
<?php
include "common.inc";
include "common.php";

$action = $_GET["action"];
if ($action == "")
  $action = $_REQUEST["action"];
echo "action: " . $action . ".<BR>";

$userId = getUserId();

$user = $_COOKIE["user"];
echo "user: " . $user . " id: $userId. <BR>" ;

$currentTime = time();
echo "Time: " . date("H:i:s", $currentTime) . "<BR>";

switch ($action)
{
  case "addPicture":
    $filename = $_GET["filename"];
    $description = $_GET["description"];
  	 $sql = "Select * from Pictures Where filename='$filename'";
    $result = mysql_query($sql) or die("Could not execute: $sql");      
    if ($row = mysql_fetch_assoc ($result))
    {
	  $id = $row["id"];
      $sql = "Update Pictures Set filename='$filename', description='$description' Where id=$id";
    }
    else
    {
      echo "$filename does not exist in database yet.";
      $sql = "Insert into Pictures (filename,description) values ( '$filename','$description')";
    }  
    echo $sql;
    query ($sql);
    break;

  case "modBookDescription":
    $bookId = $_GET["bookId"];
    $bookName = $_GET["BookName"];
    $description = $_GET["Description"];
    $sql = "Update Books Set BookName='$bookName', Description='$description' Where Id=$bookId";
    echo $sql;
    query ($sql);
    break;

  case "modifySection":
    $sectionId = $_GET["sectionId"];
    $sectionName = $_GET["sectionName"];
    $description = $_GET["description"];
	$description = str_replace ( '$2$1$','&',$description);
    $sql = "Update Sections Set SectionName='$sectionName',Description='$description' Where Id=$sectionId";
    query ($sql);
    break;

  case "":
    echo "Action not specified";
    break;

  case "register":
    $userName = strtolower($_GET["UserName"]);
    $sql = "Select * from Users Where UserName ='$userName'";
    $result = mysql_query($sql) or die("Could not execute: $sql");    
    if ($row = mysql_fetch_row($result)) 
      print ("<script>parent.alert ( 'That username is already taken, please try again.');</Script>" );
    else 
    {    
      $sql = "Insert into Users (UserName) Values ( '$userName')";
      $result = mysql_query($sql) or die("Could not execute: $sql");    
      echo ("<script>parent.window.location.href='index.php';</script>\r\n");
    }
    break;

  case "login":
    $userName = strtolower($_GET["UserName"]);
    $sql = "Select * from Users Where UserName ='$userName'";
    $result = mysql_query($sql) or die("Could not execute: $sql");    
    if ($row = mysql_fetch_row($result)) 
      print ("<script>parent.window.location.href='login.php?user=$userName';</Script>\r\n" );
    else 
    {    
      print ("<Script>parent.alert ( 'This user name was not found: $userName' );</Script>\r\n" );
    }
    break;

  case "clean":
    query ( "Delete from Books");
    query ( "Delete from Sections");
    break;

  case "createGame":
    $color = $_GET["color"];
    $hostId = $_GET["hostId"];
    $gameName = $_GET["gameName"];

    $sql = "Select * From Games Where GameName='$gameName'";
    $result = mysql_query($sql) or die("Could not execute sql: $sql");
    if ($row = mysql_fetch_row($result) && $white) 
    {
      print ("<script>alert ( 'This game name: $gameName is already in use, please choose a different name' );history.go(-1);</Script>" );
      break;
    }
    else 
    {
      $sql = "Insert Into Games (HostId,GameName,Started,Complete,MaxPlayers) Values ($hostId,'$gameName','N', 'N',2)";
      $result = mysql_query($sql) or die("Could not execute sql: $sql");

      $sql = "Select * From Games Where GameName='$gameName'";
      $result = mysql_query($sql) or die("Could not execute sql: $sql");

      if ($row = mysql_fetch_row($result)) 
        $gameId = $row[0];
      
      // Delete any entries for host for this game
      $sql = "Delete From GamePlayers Where gameId=$gameId AND userId=$hostId";
      $result = mysql_query($sql) or die ("Could not execute sql: $sql");

      // Add the host to gamePlayers, this will cause readServer to change page to lobby page
      $sql = "Insert into GamePlayers (gameId,color,userId) Values ($gameId,'$color',$hostId)";
      $result = mysql_query($sql) or die("Could not execute sql: $sql");      
    }  
    break;

  case "startGame":
    $gameId = $_GET["gameId"];
    $sql = "Update Games Set Started='Y' Where Id=$gameId";
    $result = mysql_query($sql) or die ( "Could not execute sql: $sql");
    break;

  case "hostQuitGame":
    $userId = $_GET["userId"];   
    $gameId = $_GET["gameId"];
    $sql = "Delete From GamePlayers Where GameId=$gameId";
    $result = mysql_query($sql) or die ( "Could not execute sql: $sql");
    $sql = "Delete From Games Where Id=$gameId";
    $result = mysql_query($sql) or die ( "Could not execute sql: $sql");
    print ("<script>alert ( 'Game Left');history.go(-2);</script>\r\n");  
    break;

  case "quitGame": 
    $userId = $_GET["userId"];   
    $gameId = $_GET["gameId"];
    $sql = "Update Games Set Complete = 'Y' Where Id=$gameId";
    $result = mysql_query($sql) or die ( "Could not execute sql: $sql");
    break;

  case "playerQuitGame":
    $userId = $_GET["userId"];   
    $gameId = $_GET["gameId"];
    $sql = "Delete From GamePlayers Where UserId=$userId AND GameId=$gameId";
    $result = mysql_query($sql) or die ( "Could not execute sql: $sql");
    print ("<script>alert('Game Left');history.go(-2);</script>\r\n");  
    break; 

  case "kickFromGame":
    $userId = $_GET["userId"];   
    $gameId = $_GET["gameId"];
    $sql = "Delete From GamePlayers Where UserId=$userId AND GameId=$gameId";
    $result = mysql_query($sql) or die ( "Could not execute: $sql");
    break;

  case "joinGame":
    $userId = $_GET["userId"];   
    $gameName = $_GET["gameName"];
    $sql = "Select * From Games Where GameName='$gameName'";
    $result = mysql_query($sql) or die ( "Could not execute sql: $sql");
    if ($row = mysql_fetch_assoc($result)) 
      $gameId = $row["Id"];

    // Find the color that is not in use...
    $color = $_GET["color"];   

    // Delete any previous entries for this gameplayer and gameid
    $sql = "Delete From GamePlayers Where gameId=$gameId AND userId=$userId";
    $result = mysql_query($sql) or die ("Could not execute sql: $sql");

    // Check if that color is already in use.
    $sql = "Select * From GamePlayers Where gameId=$gameId AND color='$color'";
    $result = mysql_query ($sql) or die ("Could not execute sql: $sql" );
    if ($row = mysql_fetch_assoc($result)) {
      $print ("<script> parent.msgbox ('Color: $color is already taken for that game. Please choose again'); </Script>" );
    } else {  
      $sql = "Insert Into GamePlayers (gameId,color,userId) Values ($gameId,'$color',$userId)";
      $result = mysql_query($sql) or die("Could not execute sql: $sql");
    }
    break;

  case "":
    echo "doAction.php<BR>Ready for action..<BR>";
    break; // null action

  default:
    echo "Error action not understand " . $action;
    break;
}

?>
</body>
</html>