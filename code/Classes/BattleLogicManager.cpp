#include "BattleLogicManager.h"

BattleLogicManager* BattleLogicManager::_instance = nullptr;

BattleLogicManager::BattleLogicManager(void)
{
}


BattleLogicManager::~BattleLogicManager(void)
{
}

BattleLogicManager* BattleLogicManager::getInstance()
{
	if(!_instance)
	{
		_instance = new BattleLogicManager();
	}
	return _instance;
}