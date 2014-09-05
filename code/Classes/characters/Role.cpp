#include "Role.h"

Role::Role(void)
{
	_health = 0;
	_healthMax = 0;
	_action = RoleAction::UNDEFINED;
	_worldPosition = Point(0.f, 0.f);
}

Role::~Role(void)
{
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

void Role::setWorldPosition(const Point& value)
{
	_worldPosition.x = value.x;
	_worldPosition.y = value.y;
}

void Role::setWorldPosition(float x, float y)
{
	_worldPosition.x = x;
	_worldPosition.y = y;
}

void Role::restoreOriginalAnimation()
{
	setAction(RoleAction::STAND);
}