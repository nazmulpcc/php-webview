<?php

if (!extension_loaded('parallel')) {
    die('The parallel extension is not available');
}

if (! class_exists('Webview')) {
    require __DIR__ . '/../webview.stub.php'; // ide helper
}

$ui = new \parallel\Runtime();
$worker = new \parallel\Runtime();
$channel = new \parallel\Channel;

$ui->run(function () use($channel) {
    $webview = new Webview();
    $webview->set_title('UI Thread');
    $webview->set_size(600, 450);
    $webview->set_html("
        <h2>Time: <span id='hour'>HH</span>:<span id='minute'>mm</span>:<span id='second'>ii</span> </h2>
        <button onclick='window.single_thread()'>Single Thread Callback</button>
        <button onclick='window.multi_thread()'>Multi Thread Callback</button>
    ");
    $webview->init("
        window.onload = function(){
            setInterval(function() {
                var date = new Date();
                hour.innerText = date.getHours();
                minute.innerText = date.getMinutes();
                second.innerText = date.getSeconds();
            }, 1000);
        }
    ");
    $webview->bind('single_thread', function () {
        sleep(3); // simulate a long-running task
        echo "Single Thread task finished\n";
    });
    $webview->bind('multi_thread', fn() => $channel->send(true));
    $webview->run();
    unset($webview);
    $channel->send(false); // send a signal to stop the worker
});

//$channel->setBlocking(false);
$worker->run(function () use ($channel) {
    while (true) {
        $data = $channel->recv();
        if ($data === true) {
            sleep(3); // simulate a long-running task
            echo "Multi Thread task finished\n";
        }
        if ($data === false){
            echo "Quiting the worker\n";
            break;
        }
    }
});

echo "Hello from the main thread\n"; // this will be printed immediately
