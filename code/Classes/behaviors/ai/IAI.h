#ifndef _IAI_H_
#define _IAI_H_
#pragma once

class Role;
class IAI
{
public:
	IAI(void) {};
	virtual ~IAI(void) {};

	virtual void update(float delta) = 0;
	virtual void setTarget(Role*) = 0;
};

#endif