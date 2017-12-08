<?php

// See https://github.com/frequenc1/php-osc for example code

require "php-osc/OSCClient.php";
require "php-osc/OSCDatagram.php";
require "php-osc/OSCMessage.php";
require "php-osc/Timetag.php";
require "php-osc/Infinitum.php";
require "php-osc/Blob.php";
require "php-osc/OSCBundle.php";

use PhpOSC\OSCClient;
use PhpOSC\OSCMessage;
use PhpOSC\Timetag;
use PhpOSC\Infinitum;
use PhpOSC\Blob;
use PhpOSC\OSCBundle;

$host = "127.0.0.1";
$port = 12345;
$addr = "/point";

$x = $_REQUEST['x'];
$y = $_REQUEST['y'];

$msg = new OSCMessage($addr);
$msg->add_arg($x, "i");
$msg->add_arg($y, "i");

$c = new OSCClient();
$c->set_destination($host, $port);
$c->send($msg);

echo "Message sent";

?>
