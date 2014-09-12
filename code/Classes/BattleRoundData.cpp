#include "BattleRoundData.h"


BattleRoundData::BattleRoundData()
{
	limitArea = Rect(0, 0, 0, 0);
	monsters = std::vector<BattleMonsterData*>();
}

BattleRoundData::~BattleRoundData()
{
	
}