<?php

if(! class_exists('Webview')) {
    require_once __DIR__ .'/webview.stub.php';
}

$html = <<<EOD
    <button id="increment">Tap me</button>
    <div>You tapped <span id="count">0</span> time(s).</div>
    <button id="compute">Compute</button>
    <div>Result of computation: <span id="compute-result">0</span></div>
    <button id="donothing" onclick="window.donothing()">Do Nothing</button>
    <script>
        const [incrementElement, countElement, computeElement, computeResultElement] = document.querySelectorAll("#increment, #count, #compute, #compute-result");
          document.addEventListener("DOMContentLoaded", () => {
            incrementElement.addEventListener("click", () => {
              window.increment().then(response => {
                countElement.textContent = response.count;
              });
            });
            computeElement.addEventListener("click", () => {
              computeElement.disabled = true;
              window.compute(6, 7).then(response => {
                computeResultElement.textContent = response.result;
                computeElement.disabled = false;
              });
            });
          });
    </script>
EOD;

$webview = new Webview();

$webview->set_title("Hello World");
$webview->set_size(600, 450);

$webview->bind("compute", function(int $a, int $b){
    sleep(1); // simulate a long computation
    return json_encode(["result" => $a * $b]);
});

$count = 0;
$webview->bind("increment", function() use (&$count) {
    return json_encode(["count" => ++$count]);
});

$webview->bind("donothing", function() {
    echo "This will not be executed\n";
});
$webview->unbind("donothing");

$webview->set_html($html);

$webview->run();
unset($webview);
