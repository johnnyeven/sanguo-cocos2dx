#include "BattleCommandData.h"


BattleCommandData::BattleCommandData(void):
	type(BattleCommandType::COMMAND_UNDEFINED),
	sender(nullptr),
	target(nullptr)
{
}


BattleCommandData::~BattleCommandData(void)
{
}
