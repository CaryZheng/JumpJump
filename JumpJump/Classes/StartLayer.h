//
//  StartLayer.h
//  JumpJump
//
//  Created by Cary Zheng on 14-3-25.
//
//

#ifndef __JumpJump__StartLayer__
#define __JumpJump__StartLayer__

#include "cocos2d.h"
#include "UIButton.h"

class StartLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(StartLayer);
    
    virtual bool init();
    
    void onClickStartButton(cocos2d::Ref* object, cocos2d::ui::TouchEventType type);
};

#endif /* defined(__JumpJump__StartLayer__) */
