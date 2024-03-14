<?php

if(!class_exists('Webview')) {
    require_once "../webview.stub.php";
}

$webview = new Webview;

$webview->set_title("Hello Webview");
$webview->set_size(600, 450);
$webview->set_html("<h1>Hello World</h1>");

$webview->run();
unset($webview); // must clear
