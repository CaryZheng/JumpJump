//
//  Feather.h
//  JumpJump
//
//  Created by Cary Zheng on 14-3-27.
//
//

#ifndef __JumpJump__Feather__
#define __JumpJump__Feather__

#include "cocos2d.h"

class Feather : public cocos2d::Node
{
public:
    Feather();
    ~Feather();
    
    CREATE_FUNC(Feather);
    
    virtual bool init();
    
    cocos2d::Size getFeatherSize();
    
private:
    cocos2d::Sprite* _mainSprite = nullptr;
};

#endif /* defined(__JumpJump__Feather__) */
