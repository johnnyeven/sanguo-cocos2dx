#ifndef _ROLE_H_
#define _ROLE_H_

#pragma once
#include "cocos2d.h"
#include "define.h"

USING_NS_CC;

class Role :
	public Sprite
{
public:
	float getHealth() { return _health; };
	void setHealth(float);
	float getHealthMax() { return _healthMax; };
	void setHealthMax(float);
	RoleAction getAction() { return _action; };
	void setAction(RoleAction);
	Point& getWorldPosition() { return _worldPosition; };
	void setWorldPosition(const Point&);
	void setWorldPosition(float x, float y);
    void setFocused(bool);
    bool getFocused() { return _isFocused; };
protected:
	Role(void);
	~Role(void);

private:
    bool _isFocused;
	float _health;
	float _healthMax;
	RoleAction _action;
	Point _worldPosition;

	void restoreOriginalAnimation();
};

#endif