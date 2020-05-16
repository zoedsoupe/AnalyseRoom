<?php

require '/storage/ssd4/664/12478664/public_html/database.php';

$instance = new Database();

$id = json_decode(file_get_contents('php://input'), true);

print_r($id);

var_dump($instance->updateData($id));

?>