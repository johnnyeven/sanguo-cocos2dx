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

	std::string& roleName;
	float atk;	//攻击
	float matk;	//魔攻
	float def;	//物防
	float mdef;	//魔防
	float flee;	//闪避
	float crit;	//爆击
	float speed;	//移动速度
	float health;	//生命
	float healthMax;	//最大生命
	Point worldPosition;	//坐标
};

#endif