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
$addr = "/mode/default";

$m1 = new OSCMessage($addr);

$c = new OSCClient();
$c->set_destination($host, $port);
$c->send($m1);

echo "Message sent";

?>
