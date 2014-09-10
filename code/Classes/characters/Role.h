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
	RoleAction getAction() { return _action; };
	void setAction(RoleAction);
	Point& getWorldPosition();
	void setWorldPosition(Point&);
	void setWorldPosition(float x, float y);
    void setFocused(bool);
    bool getFocused() { return _isFocused; };
	void setBackWalk(bool);
	bool getBackWalk() { return _isBackWalk; };
    
    virtual void onEnter();
protected:
	Role(void);
	~Role(void);

private:
	RoleData* _data;
    bool _isFocused;
	bool _isBackWalk;
	RoleAction _action;
	BattleScene* _scene;
	std::map<std::string, Skill*> _skillIndex;

	void restoreOriginalAnimation();
};

#endif