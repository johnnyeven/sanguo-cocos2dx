#ifndef _BATTLEMONSTERDATA_H_
#define _BATTLEMONSTERDATA_H_
#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BattleMonsterData
{
public:
	BattleMonsterData(void);
	BattleMonsterData(int, int, float, float, bool);
	~BattleMonsterData(void);

	int id;
	int count;
	float x;
	float y;
	bool flipX;
};

#endif