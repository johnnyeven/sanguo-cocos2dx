#ifndef _DEFINE_H_
#define _DEFINE_H_
#pragma once

#define BACKGROUND_OFFSETRATE .5f
#define FOREGROUND_OFFSETRATE 2.f

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
	const std::string action[11] = {
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
		"win"
	};
};

#endif