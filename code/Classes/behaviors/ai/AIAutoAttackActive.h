#ifndef _AIAutoAttackActive_H_
#define _AIAutoAttackActive_H_
#pragma once

#include "IAI.h"

class IAILockable;
class AIAutoAttackActive:
	public IAI
{
public:
	AIAutoAttackActive(void);
	AIAutoAttackActive(int);
	~AIAutoAttackActive(void);
	
	virtual void update(float delta);
	virtual void setTarget(Role*);
	virtual void setBehavior(IBehavior*);
	virtual int getPriority();
	virtual void setPriority(int);
private:
	Role* _target;
	Role* _locked;
	IAILockable* _behavior;
	int _priority;
};

#endif