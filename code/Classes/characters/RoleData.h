#ifndef _ROLE_DATA_H
#define _ROLE_DATA_H
#pragma once

#include "cocos2d.h"

USING_NS_CC;
class RoleData
{
public:
	RoleData(void);
	~RoleData(void);

	std::string& roleName;
	float atk;	//����
	float matk;	//ħ��
	float def;	//���
	float mdef;	//ħ��
	float flee;	//����
	float crit;	//����
	float speed;	//�ƶ��ٶ�
	float health;	//����
	float healthMax;	//�������
	Point worldPosition;	//����
};

#endif