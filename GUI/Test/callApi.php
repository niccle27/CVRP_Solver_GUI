<?php
$ch = curl_init();

curl_setopt($ch, CURLOPT_URL, "https://api.openrouteservice.org/v2/matrix/driving-car");
curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
curl_setopt($ch, CURLOPT_HEADER, FALSE);

curl_setopt($ch, CURLOPT_POST, TRUE);

curl_setopt($ch, CURLOPT_POSTFIELDS, '{"locations":[[9.70093,48.477473],[9.207916,49.153868],[37.573242,55.801281],[115.663757,38.106467]]}');

curl_setopt($ch, CURLOPT_HTTPHEADER, array(
    "Content-Type: application/json",
  "Accept: application/json, application/geo+json, application/gpx+xml, img/png; charset=utf-8",
  "Authorization: 5b3ce3597851110001cf6248703754048738463ba206b43ed13658a3"
));

$response = curl_exec($ch);
curl_close($ch);

$file = "testphpWrite.json";

file_put_contents($file, $response, LOCK_EX);
$a = shell_exec("./echoFirst "."\"".addslashes($response)."\"");
echo "<pre>". $a."</pre>";
// echo $a;
// var_dump($response);
