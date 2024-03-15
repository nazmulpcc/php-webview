<?php

if(! class_exists('Webview')) {
    require_once __DIR__ .'/webview.stub.php';
}

$html = <<<EOD

EOD;

$webview = new Webview();

$webview->set_title("Hello World");
$webview->set_size(600, 450);

$webview->set_html("
    <h2>Time: <span id='hour'>HH</span>:<span id='minute'>mm</span>:<span id='second'>ii</span> </h2>
");

// redirect the console log to the PHP console
$webview->init("
    window.console = {
        log: function(data){
            window.console_log(JSON.stringify(data));
        }
    }
    window.onload = function(){
        setInterval(function() {
            var date = new Date();
            hour.innerText = date.getHours();
            minute.innerText = date.getMinutes();
            second.innerText = date.getSeconds();
            console.log('Date: ' + date);
        }, 1000);
    }
");

$webview->bind('console_log', function($data){
    echo print_r(json_decode($data), true). PHP_EOL;
});

$webview->run();
unset($webview);

