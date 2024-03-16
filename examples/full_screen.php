<?php

if(! class_exists('Webview')) {
    require_once __DIR__ .'/webview.stub.php';
}

$webview = new Webview();

$webview->set_title("Hello World");

$webview->set_html(<<<HTML
<html>
<body style="margin: 0; padding: 0">
<div style="background: white; width: 100vw; height: 100vh; padding: 10px">
    <h1> Fullscreen Demo </h1>
    <p> Window maximizing doesn't work without user interaction. </p>
    <p> But we can set the window size to the <b>available screen</b> size. </p>
    <p> For mac, this is the size of the screen minus the dock & the menu bar. </p>
    <p> For windows, this is the size of the screen minus the taskbar. </p>
    <p> For linux, this is the size of the screen minus the panel. </p>
    <p> When the user actually wants to go fullscreen, we can use the <code>requestFullscreen</code> method. </p>
    <button onclick="document.querySelector('body').requestFullscreen()"> Fullscreen </button>
    <script>
        window.onload = function() {
            window.setWindowSize(window.screen.width, window.screen.height)
        };
    </script>
</body>
</html>
HTML);

$webview->bind("setWindowSize", function($width, $height) use ($webview) {
    $webview->set_size($width, $height);
});

$webview->run();
unset($webview);

