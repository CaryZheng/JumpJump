//
//  Player.cpp
//  JumpJump
//
//  Created by Cary Zheng on 14-3-25.
//
//

#include "Player.h"
#include "ResourceStrings.h"

USING_NS_CC;

Player::Player()
{

}

Player::~Player()
{
    CC_SAFE_RELEASE(_mainSprite);
}

bool Player::init()
{
    if(!Node::init())
        return false;
    
    if(nullptr == _mainSprite)
    {
        _mainSprite = Sprite::create(ResourcePic::PLAYER_FLY);
        _mainSprite->retain();
        
        Size size = _mainSprite->getContentSize();
        Vector<SpriteFrame*> spriteFrames;
        for(int i = 1; i <= 4; i++)
        {
            char imageFileName[128] = {0};
            sprintf(imageFileName, ResourcePic::PLAYER_FLY_ANIM, i);
            
            auto spriteFrame = SpriteFrame::create(imageFileName, Rect(0, 0, size.width, size.height));
            spriteFrames.pushBack(spriteFrame);
        }
        auto animation = Animation::createWithSpriteFrames(spriteFrames);
        animation->setDelayPerUnit(0.06f);
        
        auto animate = Animate::create(animation);
        
        _mainSprite->runAction(RepeatForever::create(Sequence::create(animate, animate->reverse(), NULL)));
        this->addChild(_mainSprite);
    }
    
    return true;
}

Size Player::getPlayerSize()
{
    Size size(0, 0);
    if(_mainSprite)
    {
        size = _mainSprite->getContentSize();
    }
    
    return size;
}