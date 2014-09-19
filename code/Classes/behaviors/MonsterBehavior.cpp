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
#include "../define.h"
#include "ai/IAI.h"

struct SDescendingSort
{
	bool operator() (IAI*& obj1, IAI*& obj2)
	{
		return obj1->getPriority() > obj2->getPriority();
	}
};

MonsterBehavior::MonsterBehavior():
	_target(nullptr),
	_locked(nullptr)
{
	_scene = BattleScene::getInstance();
	_halfScreenWidth = GlobalVars::scene_width >> 1;
	_halfScreenHeight = GlobalVars::scene_height >> 1;
	_aiList = std::vector<IAI*>();
}

MonsterBehavior::~MonsterBehavior()
{
    
}

void MonsterBehavior::update(float delta)
{
	updateAI(delta);
	updatePosition(delta);
	faceToLocked();
}

void MonsterBehavior::updateAI(float delta)
{
	if(_target)
	{
		for(auto ai : _aiList)
		{
			if(!ai->update(delta))
			{
				break;
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
	for(auto ai : _aiList)
	{
		ai->setTarget(_target);
	}
}

void MonsterBehavior::setLocked(Role* value)
{
	_locked = value;
	for(auto ai : _aiList)
	{
		ai->setLocked(_locked);
	}
}

Role* MonsterBehavior::getLocked()
{
	return _locked;
}

void MonsterBehavior::addAI(IAI* value)
{
	std::vector<IAI*>::iterator it = std::find(_aiList.begin(), _aiList.end(), value);
	if(it == _aiList.end())
	{
		value->setTarget(_target);
		value->setBehavior(this);
		_aiList.push_back(value);
		
		std::sort(_aiList.begin(), _aiList.end(), SDescendingSort());
	}
}

void MonsterBehavior::removeAI(IAI* value)
{
	std::vector<IAI*>::iterator it = std::find(_aiList.begin(), _aiList.end(), value);
	if(it != _aiList.end())
	{
		_aiList.erase(it);
		delete *it;
		*it = nullptr;
	}
}

void MonsterBehavior::faceToLocked()
{
	if(_target && _locked)
	{
		Point p1 = _target->getWorldPosition();
		Point p2 = _locked->getWorldPosition();
		if(p1.x < p2.x)
		{
			_target->setFlippedX(false);
		}
		else
		{
			_target->setFlippedX(true);
		}
	}
}