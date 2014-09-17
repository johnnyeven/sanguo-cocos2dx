#ifndef _IAILockable_H_
#define _IAILockable_H_
#pragma once

class Role;
class IAILockable
{
public:
	IAILockable(void) {};
	virtual ~IAILockable(void) {};

	virtual void setLocked(Role*) = 0;
};

#endif