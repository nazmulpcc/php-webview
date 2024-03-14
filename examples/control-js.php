<?php

if(!class_exists('Webview')) {
    require_once "../webview.stub.php";
}

$webview = new Webview;

$webview->set_title("Hello Webview");
$webview->set_size(600, 450);
$webview->set_html("
<html>
    <head>
        <title>title</title>
    </head>
    <body>
        <h1>Hello Webview</h1>
        <p>This is a simple webview example.</p>
        <button onclick='change_color()'>Change Color</button>
    </body>
</html>
");

// Set initial color to red
$webview->init("
    window.onload = function() {
        document.body.style.backgroundColor = 'red';
    }
");

$webview->bind("change_color", function() use ($webview) {
    $colors = ['red', 'green', 'blue', 'yellow', 'purple', 'orange', 'pink', 'brown', 'black', 'white'];
    $color = $colors[array_rand($colors)];
    $webview->eval("document.body.style.backgroundColor = '{$color}'");
});

$webview->run();
unset($webview); // must clear
