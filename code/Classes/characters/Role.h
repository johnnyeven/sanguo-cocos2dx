#ifndef _ROLE_H_
#define _ROLE_H_

#pragma once
#include "cocos2d.h"
#include "define.h"

USING_NS_CC;
class RoleData;
class BattleScene;
class Skill;
class Role :
	public Sprite
{
public:
	void setData(RoleData*);
	RoleData* getData() { return _data; };
	float getSpeed();
	void setSpeed(float);
	float getHealth();
	void setHealth(float);
	float getHealthMax();
	void setHealthMax(float);
	float getAttackRange();
	void setAttackRange(float);
	RoleAction getAction() { return _action; };
	virtual void setAction(RoleAction);
	Point& getWorldPosition();
	void setWorldPosition(Point&);
	void setWorldPosition(float x, float y);
    void setFocused(bool);
    bool getFocused() { return _isFocused; };
	void setBackWalk(bool);
	bool getBackWalk() { return _isBackWalk; };
	int getId() { return _id; };
	void setTeam(int value)
	{
		_team = value;
	};
	int getTeam()
	{
		return _team;
	};
protected:
	Role(int);
	~Role(void);
	
	RoleAction _action;
private:
	RoleData* _data;
	int _id;
	int _team;
    bool _isFocused;
	bool _isBackWalk;
	BattleScene* _scene;
	std::map<std::string, Skill*> _skillIndex;

	virtual void restoreOriginalAnimation();
};

#endif