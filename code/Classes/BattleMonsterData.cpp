#include "BattleMonsterData.h"


BattleMonsterData::BattleMonsterData():
id(0),
count(0),
x(0.f),
y(0.f)
{

}

BattleMonsterData::BattleMonsterData(int _id, int _count, float _x, float _y, bool _flipX):
id(_id),
count(_count),
x(_x),
y(_y),
flipX(_flipX)
{

}

BattleMonsterData::~BattleMonsterData()
{
	
}