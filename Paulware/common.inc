<?php
  $connection = mysql_connect ('localhost', 'root', '') or die ('Connection error!');
  if (!mysql_select_db('paulware', $connection)) die ('Could not open paulware');
?>