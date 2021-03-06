<?php

$json = array(
    'animations' =>   arrays(
        array(
            'animateName' => '1001_attack1',
            'plistFilePath' => 'images/roles/1001/p1_s2_attack1.plist',
            'fileFormat' => 'p1_s2_attack100%02i.png',
            'frameTotal' => 20,
            'delay' => 0.05,
            'restoreOriginalFrame' => false,
        ),
        array(
            'animateName' => '1001_attack2',
            'plistFilePath' => 'images/roles/1001/p1_s2_attack2.plist',
            'fileFormat' => 'p1_s2_attack200%02i.png',
            'frameTotal' => 22,
            'delay' => 0.05,
            'restoreOriginalFrame' => false,
        ),
        array(
            'animateName' => '1001_attack3',
            'plistFilePath' => 'images/roles/1001/p1_s2_attack3.plist',
            'fileFormat' => 'p1_s2_attack300%02i.png',
            'frameTotal' => 26,
            'delay' => 0.05,
            'restoreOriginalFrame' => false,
        ),
        array(
            'animateName' => '1001_attack4',
            'plistFilePath' => 'images/roles/1001/p1_s2_attack4.plist',
            'fileFormat' => 'p1_s2_attack400%02i.png',
            'frameTotal' => 31,
            'delay' => 0.05,
            'restoreOriginalFrame' => false,
        ),
        array(
            'animateName' => '1001_attack5',
            'plistFilePath' => 'images/roles/1001/p1_s2_attack5.plist',
            'fileFormat' => 'p1_s2_attack500%02i.png',
            'frameTotal' => 26,
            'delay' => 0.05,
            'restoreOriginalFrame' => false,
        ),
        array(
            'animateName' => '1001_hit',
            'plistFilePath' => 'images/roles/1001/p1_s2_hit.plist',
            'fileFormat' => 'p1_s2_hit00%02i.png',
            'frameTotal' => 14,
            'delay' => 0.05,
            'restoreOriginalFrame' => false,
        ),
        array(
            'animateName' => '1001_death',
            'plistFilePath' => 'images/roles/1001/p1_s2_hit.plist',
            'fileFormat' => 'p1_s2_death00%02i.png',
            'frameTotal' => 32,
            'delay' => 0.05,
            'restoreOriginalFrame' => false,
        ),
        array(
            'animateName' => '1001_run',
            'plistFilePath' => 'images/roles/1001/p1_s2_run.plist',
            'fileFormat' => 'p1_s2_run00%02i.png',
            'frameTotal' => 16,
            'delay' => 0.05,
            'restoreOriginalFrame' => false,
        ),
        array(
            'animateName' => '1001_stand',
            'plistFilePath' => 'images/roles/1001/p1_s2_stand.plist',
            'fileFormat' => 'p1_s2_stand00%02i.png',
            'frameTotal' => 17,
            'delay' => 0.05,
            'restoreOriginalFrame' => false,
        ),
        array(
            'animateName' => '1001_wait',
            'plistFilePath' => 'images/roles/1001/p1_s2_wait.plist',
            'fileFormat' => 'p1_s2_wait00%02i.png',
            'frameTotal' => 17,
            'delay' => 0.05,
            'restoreOriginalFrame' => false,
        ),
        array(
            'animateName' => '1001_win',
            'plistFilePath' => 'images/roles/1001/p1_s2_win.plist',
            'fileFormat' => 'p1_s2_win00%02i.png',
            'frameTotal' => 26,
            'delay' => 0.05,
            'restoreOriginalFrame' => false,
        )
    )
);

echo json_encode($json);