#include "RoleBattleData.h"
#include "skills/Skill.h"

RoleBattleData::RoleBattleData(void)
{
	normalAttackAction = std::vector<int>();
	normalAttackDelay = std::vector<float>();
	skills = std::vector<Skill*>();
}


RoleBattleData::~RoleBattleData(void)
{
}
