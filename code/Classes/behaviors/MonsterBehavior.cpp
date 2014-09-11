//
//  HeroBehavior.cpp
//  Sanguo
//
//  Created by 李翌文 on 14-9-7.
//
//

#include "MonsterBehavior.h"
#include "BattleScene.h"
#include "Joystick.h"
#include "GlobalVars.h"
#include "BattleControllPanel.h"
#include "../characters/Monster.h"

MonsterBehavior::MonsterBehavior():
	_target(nullptr)
{
	_scene = BattleScene::getInstance();
	_halfScreenWidth = GlobalVars::scene_width >> 1;
	_halfScreenHeight = GlobalVars::scene_height >> 1;
}

MonsterBehavior::~MonsterBehavior()
{
    
}

void MonsterBehavior::update(float delta)
{
	updatePosition(delta);
}

void MonsterBehavior::updatePosition(float delta)
{
	if(_target)
	{
		float targetX, targetY;
		Point p = _target->getWorldPosition();
		if(_target->getFocused())
		{
			targetX = p.x < _halfScreenWidth ? p.x : _halfScreenWidth;
			targetY = p.y < _halfScreenHeight ? p.y : _halfScreenHeight;

			targetX = p.x > (_scene->getMapWidth() - _halfScreenWidth) ? (p.x - (_scene->getMapWidth() - GlobalVars::scene_width)) : targetX;
			targetY = p.y > (_scene->getMapHeight() - _halfScreenHeight) ? (p.x - (_scene->getMapHeight() - GlobalVars::scene_height)) : targetY;
		}
		else
		{
			Point screenPosition = _scene->getScreenPosition(p.x, p.y);
			targetX = screenPosition.x;
			targetY = screenPosition.y;
		}

		_target->setPosition(targetX, targetY);
	}
}

void MonsterBehavior::setTarget(Monster* value)
{
    _target = value;
}