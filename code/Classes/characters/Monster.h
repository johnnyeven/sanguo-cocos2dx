#ifndef _MONSTER_H_
#define _MONSTER_H_

#pragma once
#include "cocos2d.h"
#include "Role.h"

USING_NS_CC;

class MonsterBehavior;

class Monster :
	public Role
{
public:
	static Monster* create(int);
	static Monster* createWithJson(const std::string&);
    virtual void update(float delta);
    void setBehavior(MonsterBehavior*);
	virtual void setAction(RoleAction) override;
private:
	Monster(int);
	~Monster(void);
    
    MonsterBehavior* _behavior;

	virtual void restoreOriginalAnimation() override;
};

#endif