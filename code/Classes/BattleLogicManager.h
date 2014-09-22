#ifndef _BattleLogicManager_H_
#define _BattleLogicManager_H_
#pragma once

class BattleLogicManager
{
public:
	static BattleLogicManager* getInstance();
	void update(float delta);
	float getTimer();
private:
	static BattleLogicManager* _instance;
	float _timer;

	BattleLogicManager(void);
	~BattleLogicManager(void);
};

#endif