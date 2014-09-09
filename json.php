<?php
$config = array(
	'animations'	=>	array(
		array(
			'animateName'			=>	'attack1',
			'plistFilePath'			=>	'images/roles/p1_s2/p1_s2_attack1.plist',
			'fileFormat'			=>	'p1_s2_attack100%02i.png',
			'frameTotal'			=>	20,
			'delay'					=>	.07,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'attack2',
			'plistFilePath'			=>	'images/roles/p1_s2/p1_s2_attack2.plist',
			'fileFormat'			=>	'p1_s2_attack200%02i.png',
			'frameTotal'			=>	22,
			'delay'					=>	.07,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'attack3',
			'plistFilePath'			=>	'images/roles/p1_s2/p1_s2_attack3.plist',
			'fileFormat'			=>	'p1_s2_attack300%02i.png',
			'frameTotal'			=>	26,
			'delay'					=>	.07,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'attack4',
			'plistFilePath'			=>	'images/roles/p1_s2/p1_s2_attack4.plist',
			'fileFormat'			=>	'p1_s2_attack400%02i.png',
			'frameTotal'			=>	31,
			'delay'					=>	.07,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'attack5',
			'plistFilePath'			=>	'images/roles/p1_s2/p1_s2_attack5.plist',
			'fileFormat'			=>	'p1_s2_attack500%02i.png',
			'frameTotal'			=>	26,
			'delay'					=>	.07,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'hit',
			'plistFilePath'			=>	'images/roles/p1_s2/p1_s2_hit.plist',
			'fileFormat'			=>	'p1_s2_death00%02i.png',
			'frameTotal'			=>	14,
			'delay'					=>	.07,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'run',
			'plistFilePath'			=>	'images/roles/p1_s2/p1_s2_run.plist',
			'fileFormat'			=>	'p1_s2_run00%02i.png',
			'frameTotal'			=>	16,
			'delay'					=>	.07,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'stand',
			'plistFilePath'			=>	'images/roles/p1_s2/p1_s2_stand.plist',
			'fileFormat'			=>	'p1_s2_stand00%02i.png',
			'frameTotal'			=>	17,
			'delay'					=>	.07,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'wait',
			'plistFilePath'			=>	'images/roles/p1_s2/p1_s2_wait.plist',
			'fileFormat'			=>	'p1_s2_wait00%02i.png',
			'frameTotal'			=>	17,
			'delay'					=>	.07,
			'restoreOriginalFrame'	=>	false
		),
		array(
			'animateName'			=>	'win',
			'plistFilePath'			=>	'images/roles/p1_s2/p1_s2_win.plist',
			'fileFormat'			=>	'p1_s2_win00%02i.png',
			'frameTotal'			=>	26,
			'delay'					=>	.07,
			'restoreOriginalFrame'	=>	false
		)
	)
);

echo json_encode($config);