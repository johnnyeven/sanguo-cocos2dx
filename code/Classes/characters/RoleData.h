#ifndef _ROLE_DATA_H
#define _ROLE_DATA_H
#pragma once

#include "cocos2d.h"

USING_NS_CC;
class RoleData
{
public:
	RoleData(void);
	~RoleData(void);

	std::string* roleName;
	float atk;	//攻击
	float matk;	//魔攻
	float def;	//防御
	float mdef;	//魔防
	float flee;	//闪避
	float crit;	//爆击
	float speed;	//行走速度
	float health;	//生命
	float healthMax;	//最大生命
	float attackRange;	//攻击距离
	/* 攻击速度 秒/次 */
	float attackRate;
	/* 当前攻速的触发器 */
	float attackRateCurrent;
	Point worldPosition;	//坐标
};

#endif