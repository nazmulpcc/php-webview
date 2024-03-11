--TEST--
test1() Basic test
--EXTENSIONS--
webview
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension webview is loaded and working!
NULL
