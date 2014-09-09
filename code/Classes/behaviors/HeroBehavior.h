//
//  HeroBehavior.h
//  Sanguo
//
//  Created by 李翌文 on 14-9-7.
//
//

#ifndef __Sanguo__HeroBehavior__
#define __Sanguo__HeroBehavior__
#pragma once

#include "cocos2d.h"
#include "IBehavior.h"
#include "../characters/Hero.h"

USING_NS_CC;

class BattleScene;
class Joystick;
class HeroBehavior:
    public IBehavior
{
public:
    HeroBehavior(void);
    virtual ~HeroBehavior(void);
    
    virtual void update(float delta);
	void updatePosition(float delta);
    void setTarget(Hero*);
    Hero* getTarget() { return _target; };
private:
    Hero* _target;
	BattleScene* _scene;
	Joystick* _joystick;
	float _halfScreenWidth;
	float _halfScreenHeight;
};

#endif /* defined(__Sanguo__HeroBehavior__) */
