#ifndef _DEFINE_H_
#define _DEFINE_H_
#pragma once

#define BACKGROUND_OFFSETRATE .5f
#define FOREGROUND_OFFSETRATE 2.f
#define MAX_AI_WAITING_TIME 1.f

enum RoleTeam
{
	PLAYER,
	MONSTER
};

enum RoleAction
{
	UNDEFINED,
	RUN,
	STAND,
	WAIT,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	ATTACK4,
	ATTACK5,
	HIT,
	WIN,
	DEATH
};

enum BehaviorMode
{
	AUTO,
	MANUAL
};

namespace GlobalConfig
{
	const std::string action[12] = {
		"",
		"run",
		"stand",
		"wait",
		"attack1",
		"attack2",
		"attack3",
		"attack4",
		"attack5",
		"hit",
		"win",
		"death"
	};
};

#endif