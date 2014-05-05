//
//  Player.h
//  JumpJump
//
//  Created by Cary Zheng on 14-3-25.
//
//

#ifndef __JumpJump__Player__
#define __JumpJump__Player__

#include "cocos2d.h"

class Player : public cocos2d::Node
{
public:
    Player();
    ~Player();

    CREATE_FUNC(Player);
    
    virtual bool init();
    
    cocos2d::Size getPlayerSize();
    
private:
    cocos2d::Sprite* _mainSprite = nullptr;
};

#endif /* defined(__JumpJump__Player__) */
