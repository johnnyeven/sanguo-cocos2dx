#include "Monster.h"
#include "../behaviors/MonsterBehavior.h"


Monster::Monster(int id):Role(id)
{
    setBehavior(new MonsterBehavior());
}


Monster::~Monster(void)
{
}

Monster* Monster::create(int id)
{
    Monster *s = new (std::nothrow) Monster(id);
    if (s && s->init())
    {
        s->autorelease();
        return s;
    }
    CC_SAFE_DELETE(s);
    return nullptr;
}

void Monster::setBehavior(MonsterBehavior* b)
{
    _behavior = b;
    _behavior->setTarget(this);
}

void Monster::update(float delta)
{
    Role::update(delta);
    
    if(_behavior)
    {
        _behavior->update(delta);
    }
}

void Monster::setAction(RoleAction value)
{
	if(_action != value)
	{
		if((value == RoleAction::ATTACK1 ||
			value == RoleAction::ATTACK2) &&
			(_action == RoleAction::ATTACK1 ||
			_action == RoleAction::ATTACK2))
		{
			return;
		}
		stopAllActions();
		_action = value;
		int index = (int)value;
		std::string name = StringUtils::format("%i_%s", getId(), GlobalConfig::action[index].c_str());
		CCAnimate* animate = CCAnimate::create(CCAnimationCache::getInstance()->getAnimation(name));
		if(index < 4)
		{
			runAction(CCRepeatForever::create(animate));
		}
		else
		{
			runAction(CCSequence::create(animate, CallFunc::create(CC_CALLBACK_0(Monster::restoreOriginalAnimation, this)), NULL));
		}
	}
}

void Monster::restoreOriginalAnimation()
{
	setAction(RoleAction::STAND);
}