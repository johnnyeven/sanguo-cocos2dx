<?php

$config = array(
	'plistFile'			=>	'images/maps/1001.plist',
	'width'				=>	3600,
	'height'			=>	640,
	'minY'				=>	100,
	'maxY'				=>	320,
	'startX'			=>	100,
	'startY'			=>	200,
	'rounds'			=>	array(
		array(
			'limitArea'		=>	array(
				'x'		=>	0,
				'y'		=>	100,
				'width'	=>	3600,
				'height'=>	220
			),
			'monster'		=>	array(
				'id'	=>	2001,
				'count'	=>	1,
				''
			)
		)
	)
);

echo json_encode($config);