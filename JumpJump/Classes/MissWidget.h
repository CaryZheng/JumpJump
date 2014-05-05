//
//  MissWidget.h
//  JumpJump
//
//  Created by Cary Zheng on 14-3-27.
//
//

#ifndef __JumpJump__MissWidget__
#define __JumpJump__MissWidget__

#include "cocos2d.h"

class MissWidget : public cocos2d::Node
{
public:
    CREATE_FUNC(MissWidget);
    
    virtual bool init();
    
    void addMissItem();
    int getMissItemNum();
    
private:
    cocos2d::Vector<cocos2d::Sprite*> _missItems;
};

#endif /* defined(__JumpJump__MissWidget__) */
