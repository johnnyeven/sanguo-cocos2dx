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
class BattleCommandData
{
public:
	/* �������� */
	BattleCommandType type;
	/* ������� */
	Role* sender;
	/* ����Ŀ�� */
	Vector<Role*> target;
	/* ��ʱ���� */
	float delay;
	/* ����ID */
	int skillId;

	BattleCommandData(void);
	~BattleCommandData(void);

	static BattleCommandData* createAttackCommand(Role* _sender, Role* _target, float _delay);
};

#endif