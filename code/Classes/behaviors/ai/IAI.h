#ifndef _IAI_H_
#define _IAI_H_
#pragma once

class Role;
class IBehavior;
class IAI
{
public:
	IAI(void) {};
	virtual ~IAI(void) {};

	virtual void update(float delta) = 0;
	virtual void setTarget(Role*) = 0;
	virtual void setLocked(Role*) = 0;
	virtual void setBehavior(IBehavior*) = 0;
	virtual int getPriority() = 0;
	virtual void setPriority(int) = 0;
};

#endif