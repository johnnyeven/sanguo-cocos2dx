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

USING_NS_CC;

class Monster;
class Role;
class BattleScene;
class MonsterBehavior:
	public IBehavior, IAutoAI
{
public:
    MonsterBehavior(void);
    virtual ~MonsterBehavior(void);
    
    virtual void update(float delta);
	virtual void updatePosition(float delta);
	virtual void updateAI(float delta);
    void setTarget(Monster*);
    Monster* getTarget() { return _target; };
private:
    Monster* _target;
	Role* _locked;
	Point _targetPosition;
	BattleScene* _scene;
	float _halfScreenWidth;
	float _halfScreenHeight;
};

#endif /* defined(__Sanguo__HeroBehavior__) */
