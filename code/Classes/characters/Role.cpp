#include "Role.h"
#include "../BattleScene.h"
#include "../skills/Skill.h"
#include "RoleData.h"

Role::Role(int id):
_id(id)
{
	_team = 0;
	_action = RoleAction::UNDEFINED;
	_isFocused = false;
	_isBackWalk = false;
    _scene = BattleScene::getInstance();
	_skillIndex = std::map<std::string, Skill*>();
}

Role::~Role(void)
{
	_skillIndex.clear();
}

void Role::setData(RoleData* data)
{
	_data = data;
	setSpeed(data->speed);
	setHealth(data->health);
	setHealthMax(data->healthMax);
	setWorldPosition(data->worldPosition);
}

void Role::setAtk(float value)
{
	_data->atk = value;
}

float Role::getAtk()
{
    return _data->atk;
}

void Role::setMatk(float value)
{
	_data->matk = value;
}

float Role::getMatk()
{
    return _data->matk;
}

void Role::setDef(float value)
{
	_data->def = value;
}

float Role::getDef()
{
    return _data->def;
}

void Role::setMdef(float value)
{
	_data->mdef = value;
}

float Role::getMdef()
{
    return _data->mdef;
}

void Role::setFlee(float value)
{
	_data->flee = value;
}

float Role::getFlee()
{
    return _data->flee;
}

void Role::setCrit(float value)
{
	_data->crit = value;
}

float Role::getCrit()
{
    return _data->crit;
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

float Role::getAttackRange()
{
	return _data->attackRange;
}

void Role::setAttackRange(float value)
{
	_data->attackRange = value;
}

float Role::getAttackRate()
{
	return _data->attackRate;
}

void Role::setAttackRate(float value)
{
	_data->attackRate = value;
}

float Role::getAttackRateCurrent()
{
	return _data->attackRateCurrent;
}

void Role::setAttackRateCurrent(float value)
{
	_data->attackRateCurrent = value;
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
		std::string name = StringUtils::format("%i_%s", _id, GlobalConfig::action[index].c_str());
		CCAnimate* animate = CCAnimate::create(CCAnimationCache::getInstance()->getAnimation(name));
		if(index < 4)
		{
			runAction(CCRepeatForever::create(animate));
		}
		else if(index < 11)
		{
			runAction(CCSequence::create(animate, CallFunc::create(CC_CALLBACK_0(Role::restoreOriginalAnimation, this)), NULL));
		}
		else
		{
			runAction(animate);
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