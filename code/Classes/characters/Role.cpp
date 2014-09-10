#include "Role.h"
#include "../BattleScene.h"

Role::Role(void)
{
	_speed = 0;
	_health = 0;
	_healthMax = 0;
	_action = RoleAction::UNDEFINED;
	_worldPosition = Point(0.f, 0.f);
	_isFocused = false;
	_isBackWalk = false;
	_scene = nullptr;
}

Role::~Role(void)
{
}

void Role::onEnter()
{
    Sprite::onEnter();
    _scene = BattleScene::getInstance();
}

void Role::setSpeed(float value)
{
	_speed = value;
}

void Role::setHealth(float value)
{
	_health = value;
}

void Role::setHealthMax(float value)
{
	_healthMax = value;
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
	_worldPosition.x = value.x;
	_worldPosition.y = value.y;
}

void Role::setWorldPosition(float x, float y)
{
    Rect* limit = _scene->getLimitArea();
    if(limit)
    {
        x = std::min(limit->getMaxX(), std::max(limit->getMinX(), x));
        y = std::min(limit->getMaxY(), std::max(limit->getMinY(), y));
    }
	_worldPosition.x = x;
	_worldPosition.y = y;
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