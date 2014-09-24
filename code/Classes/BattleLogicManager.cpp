#include "BattleLogicManager.h"
#include "BattleCommandData.h"
#include "characters/Role.h"
#include "define.h"

BattleLogicManager* BattleLogicManager::_instance = nullptr;

BattleLogicManager::BattleLogicManager(void):
	_timer(0)
{
	_commandList = std::vector<BattleCommandData*>();
}


BattleLogicManager::~BattleLogicManager(void)
{
	_commandList.clear();
}

void BattleLogicManager::update(float delta)
{
	_timer += delta;

	for(int i = 0; i < _commandList.size(); ++i)
	{
		auto item = _commandList.at(i);
		if(item->delay <= _timer)
		{
			if(item->type == BattleCommandType::ATTACK)
			{
				handleAttackCommand(item->sender, item->target);
			}
			removeCommand(item);
			log("trigger");
		}
	}
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

void BattleLogicManager::addCommand(BattleCommandData* data)
{
	std::vector<BattleCommandData*>::iterator it = std::find(_commandList.begin(), _commandList.end(), data);
	if(it == _commandList.end())
	{
		data->delay += _timer;
		_commandList.push_back(data);
	}
}

void BattleLogicManager::removeCommand(BattleCommandData* data)
{
	std::vector<BattleCommandData*>::iterator it = std::find(_commandList.begin(), _commandList.end(), data);
	if(it != _commandList.end())
	{
		_commandList.erase(it);
	}
}

void BattleLogicManager::removeCommand(int index)
{
	if(_commandList.size() > index)
	{
		std::vector<BattleCommandData*>::iterator it = _commandList.begin() + index;
		_commandList.erase(it);
	}
}

void BattleLogicManager::removeCommands()
{
	_commandList.clear();
}

void BattleLogicManager::handleAttackCommand(Role* sender, std::vector<Role*>& target)
{
	float atk = sender->getAtk();

	for(auto t : target)
	{
		float def = t->getDef();
		float damage = std::max(1.f, atk - def);

		float targetHealth = t->getHealth();
		log("damage: %f", damage);
		if(targetHealth <= damage)
		{
			//dead
			t->setAction(RoleAction::DEATH);
		}
		else
		{
			t->setHealth(targetHealth - damage);
		}
	}
}