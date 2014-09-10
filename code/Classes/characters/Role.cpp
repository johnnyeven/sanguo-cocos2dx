#include "Role.h"
#include "../BattleScene.h"
#include "../skills/Skill.h"
#include "RoleData.h"

Role::Role(void)
{
	_action = RoleAction::UNDEFINED;
	_isFocused = false;
	_isBackWalk = false;
	_scene = nullptr;
	_skillIndex = std::map<std::string, Skill*>();
}

Role::~Role(void)
{
}

void Role::onEnter()
{
    Sprite::onEnter();
    _scene = BattleScene::getInstance();
}

void Role::setData(RoleData* data)
{
	_data = data;
	setSpeed(data->speed);
	setHealth(data->health);
	setHealthMax(data->healthMax);
	setWorldPosition(data->worldPosition);
}

void Role::setSpeed(float value)
{
	_data->speed = value;
}

float Role::getSpeed()
{
    return _data->speed;
}

void Role::setHealth(float value)
{
	_data->health = value;
}

float Role::getHealth()
{
    return _data->health;
}

void Role::setHealthMax(float value)
{
	_data->healthMax = value;
}

float Role::getHealthMax()
{
    return _data->healthMax;
}

void Role::setAction(RoleAction value)
{
	if(_action != value)
	{
		if((value == RoleAction::ATTACK1 ||
			value == RoleAction::ATTACK2 ||
			value == RoleAction::ATTACK3 ||
			value == RoleAction::ATTACK4 ||
			value == RoleAction::ATTACK5) &&
			(_action == RoleAction::ATTACK1 ||
			_action == RoleAction::ATTACK2 ||
			_action == RoleAction::ATTACK3 ||
			_action == RoleAction::ATTACK4 ||
			_action == RoleAction::ATTACK5))
		{
			return;
		}
		stopAllActions();
		_action = value;
		int index = (int)value;
		std::string name = GlobalConfig::action[index];
		CCAnimate* animate = CCAnimate::create(CCAnimationCache::getInstance()->getAnimation(name));
		if(index < 4)
		{
			runAction(CCRepeatForever::create(animate));
		}
		else
		{
			runAction(CCSequence::create(animate, CallFunc::create(CC_CALLBACK_0(Role::restoreOriginalAnimation, this)), NULL));
		}
	}
}

void Role::setWorldPosition(Point& value)
{
    Rect* limit = _scene->getLimitArea();
    if(limit)
    {
        value.x = std::min(limit->getMaxX(), std::max(limit->getMinX(), value.x));
        value.y = std::min(limit->getMaxY(), std::max(limit->getMinY(), value.y));
    }
	_data->worldPosition.x = value.x;
	_data->worldPosition.y = value.y;
}

void Role::setWorldPosition(float x, float y)
{
    Rect* limit = _scene->getLimitArea();
    if(limit)
    {
        x = std::min(limit->getMaxX(), std::max(limit->getMinX(), x));
        y = std::min(limit->getMaxY(), std::max(limit->getMinY(), y));
    }
	_data->worldPosition.x = x;
	_data->worldPosition.y = y;
}

Point& Role::getWorldPosition()
{
    return _data->worldPosition;
}

void Role::setFocused(bool value)
{
    _isFocused = value;
}

void Role::setBackWalk(bool value)
{
	if(_isBackWalk != value)
	{
		_isBackWalk = value;
		setFlippedX(_isBackWalk);
	}
}

void Role::restoreOriginalAnimation()
{
	setAction(RoleAction::STAND);
}