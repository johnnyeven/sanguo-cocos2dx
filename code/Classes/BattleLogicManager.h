#ifndef _BattleLogicManager_H_
#define _BattleLogicManager_H_
#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BattleCommandData;
class BattleLogicManager
{
public:
	static BattleLogicManager* getInstance();
	void update(float delta);
	float getTimer();
	void addCommand(BattleCommandData*);
	void removeCommand(BattleCommandData*);
	void removeCommand(int);
	void removeCommands();
private:
	static BattleLogicManager* _instance;
	float _timer;
	std::vector<BattleCommandData*> _commandList;

	BattleLogicManager(void);
	~BattleLogicManager(void);
};

#endif