//
//  HeroBehavior.h
//  Sanguo
//
//  Created by 李翌文 on 14-9-7.
//
//

#ifndef __Sanguo__MonsterBehavior__
#define __Sanguo__MonsterBehavior__
#pragma once

#include "cocos2d.h"
#include "IBehavior.h"
#include "IAutoAI.h"
#include "ai/IAILockable.h"

USING_NS_CC;

class Monster;
class Role;
class BattleScene;
class IAI;
class MonsterBehavior:
	public IBehavior,
	public IAutoAI,
	public IAILockable
{
public:
    MonsterBehavior(void);
    virtual ~MonsterBehavior(void);
    
    virtual void update(float delta);
	virtual void updatePosition(float delta);
	virtual void updateAI(float delta);
	virtual void addAI(IAI*);
	virtual void removeAI(IAI*);
    void setTarget(Monster*);
    Monster* getTarget() { return _target; };
	virtual void setLocked(Role*);
	virtual Role* getLocked();
private:
    Monster* _target;
	Role* _locked;
	BattleScene* _scene;
	float _halfScreenWidth;
	float _halfScreenHeight;
	std::vector<IAI*> _aiList;
	
	void faceToLocked();
};

#endif /* defined(__Sanguo__HeroBehavior__) */
