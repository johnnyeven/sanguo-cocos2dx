#ifndef _BattleLogicManager_H_
#define _BattleLogicManager_H_
#pragma once

class BattleLogicManager
{
public:
	static BattleLogicManager* getInstance();
private:
	static BattleLogicManager* _instance;

	BattleLogicManager(void);
	~BattleLogicManager(void);
};

#endif