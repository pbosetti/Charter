#!/usr/bin/env php
<?php

require_once(__DIR__ . '/charter_client.class.php');

$ch = new charter_client(1);
$ch->clear();

for ($i = 0; $i < 200; ++$i) {
    $ch->send(array(
        $i / 10,
        sin($i / 10),
        1.1 * cos($i / 10),
        0.7 * sin($i / 10)
    ));
}

$ch->names(array('speed', 'velocity', 'acceleration'));
// $ch->close();
