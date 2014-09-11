#ifndef _HERO_H_
#define _HERO_H_

#pragma once
#include "cocos2d.h"
#include "Role.h"

USING_NS_CC;

class HeroBehavior;

class Hero :
	public Role
{
public:
	static Hero* create(int);
    virtual void update(float delta);
    void setBehavior(HeroBehavior*);
private:
	Hero(int);
	~Hero(void);
    
    HeroBehavior* _behavior;
};

#endif