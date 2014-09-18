#ifndef _IAILockable_H_
#define _IAILockable_H_
#pragma once

class Role;
class IAILockable
{
public:
	virtual void setLocked(Role*) {};
	virtual Role* getLocked() = 0;
};

#endif