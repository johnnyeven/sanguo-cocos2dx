#ifndef _AIAutoTrack_H_
#define _AIAutoTrack_H_
#pragma once

#include "IAI.h"
#include "IAILockable.h"

class BattleScene;
class Role;
class AIAutoTrack:
	public IAI, IAILockable
{
public:
	AIAutoTrack(void);
	~AIAutoTrack(void);
	
	virtual void update(float delta);
	virtual void setTarget(Role*);
	virtual void setLocked(Role*);
private:
	BattleScene* _scene;
	Role* _target;
	Role* _locked;
	float _maxAIWaitingTime;
};

#endif