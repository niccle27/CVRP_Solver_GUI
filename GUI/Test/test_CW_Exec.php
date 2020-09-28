<?php
// ob_start();
// var_dump($_POST);
// $result = ob_get_clean();
$json = $_POST["json"];
$jsonEscaped = escapeshellarg($json); // otherwise <<"key">> appear like <<key>>
// echo $json;
// $output = exec('./clarkeAndWright '.$jsonEscaped);
$output = exec('./mockOutputVehicles '.$jsonEscaped);
// $output = exec('./clarkeAndWright '.$jsonEscaped);
// $output = exec('echo '.$jsonEscaped);
// $a = exec('./test '.);
echo $output;

?>
