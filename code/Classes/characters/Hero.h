#ifndef _HERO_H_
#define _HERO_H_

#pragma once
#include "cocos2d.h"
#include "Role.h"

USING_NS_CC;

class Hero :
	public Role
{
public:
	static Hero* create();
private:
	Hero(void);
	~Hero(void);
};

#endif