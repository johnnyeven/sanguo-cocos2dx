<?php
$config = array(
	'animations'	=>	array(
		array(
			'animateName'			=>	'2001_attack1',
			'plistFilePath'			=>	'images/roles/2001/attack1.plist',
			'fileFormat'			=>	'attack1_000%02i.png',
			'frameTotal'			=>	30,
			'delay'					=>	.05,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'2001_attack2',
			'plistFilePath'			=>	'images/roles/2001/attack2.plist',
			'fileFormat'			=>	'attack2_000%02i.png',
			'frameTotal'			=>	28,
			'delay'					=>	.05,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'2001_run',
			'plistFilePath'			=>	'images/roles/2001/run.plist',
			'fileFormat'			=>	'run_000%02i.png',
			'frameTotal'			=>	18,
			'delay'					=>	.05,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'2001_stand',
			'plistFilePath'			=>	'images/roles/2001/stand.plist',
			'fileFormat'			=>	'stand_000%02i.png',
			'frameTotal'			=>	16,
			'delay'					=>	.05,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'2001_death',
			'plistFilePath'			=>	'images/roles/2001/die.plist',
			'fileFormat'			=>	'die_000%02i.png',
			'frameTotal'			=>	15,
			'delay'					=>	.05,
			'restoreOriginalFrame'	=>	false
		)
	)
);

echo json_encode($config);