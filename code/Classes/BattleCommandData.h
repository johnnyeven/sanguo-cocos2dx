#ifndef _BattleCommandData_H_
#define _BattleCommandData_H_
#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum BattleCommandType
{
	COMMAND_UNDEFINED,
	ATTACK,
	SKILL
};

class Role;
class Skill;

class BattleCommandData
{
public:
	/* 命令类型 */
	BattleCommandType type;
	/* 命令发送者 */
	Role* sender;
	/* 命令目标 */
	std::vector<Role*> target;
	/* 延时触发 */
	float delay;
	/* 技能 */
	Skill* skill;

	BattleCommandData(void);
	~BattleCommandData(void);

	static BattleCommandData* createAttackCommand(Role* _sender, Role* _target, float _delay);
};

#endif