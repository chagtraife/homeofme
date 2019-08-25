<?php
require 'phpMQTT.php';



$server = '192.168.1.137';     // change if necessary
$port = 1883;                     // change if necessary
$username = "";                   // set your username
$password = "";                   // set your password
// $client_id = "phpMQTT-publisher"; // make sure this is unique for connecting to sever - you could use uniqid()

$topic = 'light';
$client_id = "phpMQTT-publisher";

$message = "turn_off";

$mqtt = new Bluerhinos\phpMQTT($server, $port, $client_id);
if ($mqtt->connect(true, NULL, $username, $password)) {
    $mqtt->publish($topic, $message, 0);
    echo "Published message: " . $message;
    $mqtt->close();
}else{
    echo "Fail or time out<br />";
}