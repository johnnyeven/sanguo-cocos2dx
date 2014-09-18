#include "AIAutoAttackActive.h"
#include "../../characters/Role.h"
#include "../../define.h"
#include "../../behaviors/IBehavior.h"
#include "IAILockable.h"


AIAutoAttackActive::AIAutoAttackActive(void):
	_target(nullptr),
	_locked(nullptr),
	_behavior(nullptr)
{
}

AIAutoAttackActive::AIAutoAttackActive(int priority):
	_target(nullptr),
	_locked(nullptr),
	_behavior(nullptr),
	_priority(priority)
{
}

AIAutoAttackActive::~AIAutoAttackActive(void)
{
}


void AIAutoAttackActive::update(float delta)
{
	if(_target && _locked)
	{
		float attackRange = _target->getAttackRange();
		Point p1 = _target->getWorldPosition();
		Point p2 = _locked->getWorldPosition();
		float d = p1.distance(p2);
		if(d <= attackRange)
		{
			//start attack
			int i = rand() % 2 + 4;
			_target->setAction(RoleAction(i));
		}
	}
}

void AIAutoAttackActive::setTarget(Role* value)
{
	_target = value;
}

void AIAutoAttackActive::setLocked(Role* value)
{
	_locked = value;
}

void AIAutoAttackActive::setBehavior(IBehavior* b)
{
	if(dynamic_cast<IAILockable*>(b))
	{
		_behavior = dynamic_cast<IAILockable*>(b);
		_locked = _behavior->getLocked();
	}
	else
	{
		_behavior = nullptr;
	}
}

int AIAutoAttackActive::getPriority()
{
	return _priority;
}

void AIAutoAttackActive::setPriority(int value)
{
	_priority = value;
}