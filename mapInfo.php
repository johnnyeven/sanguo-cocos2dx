<?php

$config = array(
	'plistFile'			=>	'images/maps/1001.plist',
	'width'				=>	3600,
	'height'			=>	640,
	'minY'				=>	100,
	'maxY'				=>	320,
	'startX'			=>	100,
	'startY'			=>	200
);

echo json_encode($config);