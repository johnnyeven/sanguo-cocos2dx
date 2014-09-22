#include "BattleLogicManager.h"

BattleLogicManager* BattleLogicManager::_instance = nullptr;

BattleLogicManager::BattleLogicManager(void):
	_timer(0)
{
}


BattleLogicManager::~BattleLogicManager(void)
{
}

void BattleLogicManager::update(float delta)
{
	_timer += delta;
}

float BattleLogicManager::getTimer()
{
	return _timer;
}

BattleLogicManager* BattleLogicManager::getInstance()
{
	if(!_instance)
	{
		_instance = new BattleLogicManager();
	}
	return _instance;
}