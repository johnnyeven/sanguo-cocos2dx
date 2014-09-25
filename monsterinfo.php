<?php

$json = array(
	'id'		=>	2001,
	'anchor'	=>	array(
		'x'		=>	.5,
		'y'		=>	.25
	),
	'atk'			=>	140,
	'matk'			=>	0,
	'def'			=>	100,
	'mdef'			=>	150,
	'flee'			=>	100,
	'crit'			=>	90,
	'speed'			=>	200,
	'health'		=>	500,
	'attackRange'	=>	80,
	'attackRate'	=>	2,
	'battle'	=>	array(
		'normal'	=>	array(
			'type'		=>	0,		//0=只有一个动作 1=连招 2=连续播放
			'action'	=>	array('attack1'),
			'delay'		=>	array(0.5)		//伤害计算延时
		),
		'skills'	=>	array(
			array(
				'name'		=>	'重击',
				'action'	=>	array('attack2'),
				'effect'	=>	array(),
				'delay'		=>	array(0.7)
			)
		)
	)
);

echo json_encode($json);