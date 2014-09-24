#ifndef _RoleBattleData_H_
#define _RoleBattleData_H_
#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum NormalAttackType
{
	ONE,		//只有一个动作
	COMBO,		//连招
	FLOW		//连续播放
};

class Skill;

class RoleBattleData
{
public:
	RoleBattleData(void);
	~RoleBattleData(void);

	NormalAttackType normalAttackType;
	std::vector<int> normalAttackAction;
	std::vector<float> normalAttackDelay;

	std::vector<Skill*> skills;
};

#endif