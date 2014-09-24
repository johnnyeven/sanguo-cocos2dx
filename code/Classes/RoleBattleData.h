#ifndef _RoleBattleData_H_
#define _RoleBattleData_H_
#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum NormalAttackType
{
	ONE,		//ֻ��һ������
	COMBO,		//����
	FLOW		//��������
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