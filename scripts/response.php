<?php 
// $arr = array('a'=>1, 'b'=>2, 'c'=>3);

// #$json = json_encode($_GET['rows']);
// $data = array('rows' => $_GET['rows']);
// $json = json_encode($data);
// $callback = $_GET['rows'];

$data = array('rows' => $_GET['rows']);

$json = json_encode($data);

$callback = $_GET['callback'];

exit($callback."$json"); ?>