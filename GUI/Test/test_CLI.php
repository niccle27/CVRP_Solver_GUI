<?php
 // $ret = print_r($_POST,true);
 // $ret = var_export($_POST,true);

 // var_dump($_POST);
 // echo $ret
?>

<?php
ob_start();
var_dump($_POST);
$result = ob_get_clean();
?>

<?php
    // phpinfo();
    ?>

<?php
// Outputs all the result of shellcommand "ls", and returns
// the last output line into $last_line. Stores the return value
// of the shell command in $retval.

// $last_line = system('./main', $retval);

// echo' <hr />Return value: ' . $retval;
    ?>


<?php
// outputs the username that owns the running php/httpd process
// (on a system with the "whoami" executable in the path)
// $a=exec('./main');
// echo $ret
// $ret = '"'.$ret.'"';
// echo $ret;

echo $result;
$a = exec('echo '.'"'.$result.'"');
echo $a;
// $a = exec('echo '. "this is \n a test"); // cannot use \n, only this is is passed,

// var_dump($a);

   // echo $a;
// echo $ret
// echo exec('echo '. $ret);
?>
