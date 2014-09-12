#ifndef _BATTLEROUNDDATA_H_
#define _BATTLEROUNDDATA_H_
#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BattleMonsterData;
class BattleRoundData
{
public:
	BattleRoundData(void);
	~BattleRoundData(void);

	Rect limitArea;
	std::vector<BattleMonsterData*> monsters;
};

#endif