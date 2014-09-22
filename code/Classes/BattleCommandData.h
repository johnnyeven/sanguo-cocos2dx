#ifndef _BattleCommandData_H_
#define _BattleCommandData_H_
#pragma once

enum BattleCommandType
{
	COMMAND_UNDEFINED,
	ATTACK,
	SKILL
};

class Role;
class BattleCommandData
{
public:
	/* 命令类型 */
	BattleCommandType type;
	/* 命令发送者 */
	Role* sender;
	/* 命令目标 */
	Role* target;
	/* 延时触发 */
	float delay;
	/* 技能ID */
	int skillId;

	BattleCommandData(void);
	~BattleCommandData(void);
};

#endif