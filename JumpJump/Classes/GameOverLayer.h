//
//  GameOverLayer.h
//  JumpJump
//
//  Created by Cary Zheng on 14-3-27.
//
//

#ifndef __JumpJump__GameOverLayer__
#define __JumpJump__GameOverLayer__

#include "cocos2d.h"
#include "UIButton.h"

class GameOverLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int score);
    static GameOverLayer* create(int score);
    
    virtual bool init(int score);
    
    void onClickMainMenuButton(cocos2d::Ref* object, cocos2d::ui::TouchEventType type);
    void onClickRestartButton(cocos2d::Ref* object, cocos2d::ui::TouchEventType type);
};

#endif /* defined(__JumpJump__GameOverLayer__) */
