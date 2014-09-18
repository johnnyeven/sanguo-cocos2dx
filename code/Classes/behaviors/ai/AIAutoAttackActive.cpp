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

}

void AIAutoAttackActive::setTarget(Role* value)
{
	_target = value;
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