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
	/* �������� */
	BattleCommandType type;
	/* ������� */
	Role* sender;
	/* ����Ŀ�� */
	Role* target;
	/* ��ʱ���� */
	float delay;
	/* ����ID */
	int skillId;

	BattleCommandData(void);
	~BattleCommandData(void);
};

#endif