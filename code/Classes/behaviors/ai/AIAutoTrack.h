#ifndef _AIAutoTrack_H_
#define _AIAutoTrack_H_
#pragma once

#include "IAI.h"

class BattleScene;
class Role;
class IAILockable;
class AIAutoTrack:
	public IAI
{
public:
	AIAutoTrack(void);
	AIAutoTrack(int);
	~AIAutoTrack(void);
	
	virtual bool update(float delta);
	virtual void setTarget(Role*);
	virtual void setLocked(Role*);
	virtual void setBehavior(IBehavior*);
	virtual int getPriority();
	virtual void setPriority(int);
private:
	BattleScene* _scene;
	Role* _target;
	Role* _locked;
	IAILockable* _behavior;
	float _maxAIWaitingTime;
	int _priority;
};

#endif