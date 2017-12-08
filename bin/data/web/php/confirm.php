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
$addr = "/confirm";

$x1 = $_REQUEST['x1'];
$y1 = $_REQUEST['y1'];
$x2 = $_REQUEST['x2'];
$y2 = $_REQUEST['y2'];
$x3 = $_REQUEST['x3'];
$y3 = $_REQUEST['y3'];
$x4 = $_REQUEST['x4'];
$y4 = $_REQUEST['y4'];

$msg = new OSCMessage($addr);
$msg->add_arg($x1, "i");
$msg->add_arg($y1, "i");
$msg->add_arg($x2, "i");
$msg->add_arg($y2, "i");
$msg->add_arg($x3, "i");
$msg->add_arg($y3, "i");
$msg->add_arg($x4, "i");
$msg->add_arg($y4, "i");

$c = new OSCClient();
$c->set_destination($host, $port);
$c->send($msg);

echo "Message sent";

?>
