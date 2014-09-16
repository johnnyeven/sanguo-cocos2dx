//
//  IBehavior.h
//  Sanguo
//
//  Created by 李翌文 on 14-9-7.
//
//

#ifndef __Sanguo__IBehavior__
#define __Sanguo__IBehavior__
#pragma once

class IBehavior
{
public:
    IBehavior(void) {};
    virtual ~IBehavior(void) {};
    
    virtual void update(float delta) = 0;
	virtual void updatePosition(float delta) = 0;
};

#endif /* defined(__Sanguo__IBehavior__) */
