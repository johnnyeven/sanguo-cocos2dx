#include "BattleCommandData.h"


BattleCommandData::BattleCommandData(void):
	type(BattleCommandType::COMMAND_UNDEFINED),
	sender(nullptr)
{
	target = std::vector<Role*>();
}


BattleCommandData::~BattleCommandData(void)
{
	target.clear();
}

BattleCommandData* BattleCommandData::createAttackCommand(Role* _sender, Role* _target, float _delay)
{
	auto data = new BattleCommandData();
	data->type = BattleCommandType::ATTACK;
	data->sender = _sender;
	data->target.push_back(_target);
	data->delay = _delay;

	return data;
}
