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
#include "../characters/Role.h"

MonsterBehavior::MonsterBehavior():
	_target(nullptr),
	_locked(nullptr),
	_targetPosition(Point(0, 0))
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
	updateAI(delta);
	updatePosition(delta);
}

void MonsterBehavior::updateAI(float delta)
{
	if(_target)
	{
		RoleAction a = _target->getAction();
		if(a == RoleAction::ATTACK1 ||
			 a == RoleAction::ATTACK2 ||
			 a == RoleAction::ATTACK3 ||
			 a == RoleAction::ATTACK4 ||
			 a == RoleAction::ATTACK5)
		{
			return;
		}
		if(!_locked)
		{
			//选取敌对阵营离自己最近的角色锁定
			std::map< int, std::vector< Role* > > teamMap = _scene->getTeamMap();
			int team = !_target->getTeam();
			std::map< int, std::vector< Role* > >::iterator it = teamMap.find(team);
			if(it != teamMap.end())
			{
				std::vector< Role* > tmpList = it->second;
				float minDistance = FLT_MAX;
				Role* role = nullptr;
				for(auto item : tmpList)
				{
					Point p1 = _target->getWorldPosition();
					Point p2 = item->getWorldPosition();
					float d = p1.distance(p2);
					if(d < minDistance)
					{
						minDistance = d;
						role = item;
					}
				}
				_locked = role;
			}
		}
		else
		{
			Point p1 = _target->getWorldPosition();
			Point p2 = _locked->getWorldPosition();
			if(p1 != p2)
			{
				Point p = p2 - p1;
				float angle = p.getAngle();
				float x = p1.x + _target->getSpeed() * cosf(angle) * delta;
				float y = p1.y + _target->getSpeed() * sinf(angle) * delta;
				if(abs(p2.x - x) < 10.f)
					x = p2.x;
				if(abs(p2.y - y) < 10.f)
					y = p2.y;
				_target->setWorldPosition(x, y);
			}
		}
	}
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