//
//  IAutoAI.h
//  Sanguo
//
//  Created by 李翌文 on 14-9-7.
//
//

#ifndef __Sanguo__IAutoAI__
#define __Sanguo__IAutoAI__
#pragma once

class IAI;
class IAutoAI
{
public:
    IAutoAI(void) {};
    virtual ~IAutoAI(void) {};
    
	virtual void updateAI(float delta) = 0;
	virtual void addAI(IAI*) = 0;
	virtual void removeAI(IAI*) = 0;
};

#endif /* defined(__Sanguo__IAutoAI__) */
