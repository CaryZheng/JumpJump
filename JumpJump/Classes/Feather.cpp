//
//  Feather.cpp
//  JumpJump
//
//  Created by Cary Zheng on 14-3-27.
//
//

#include "Feather.h"
#include "ResourceStrings.h"

USING_NS_CC;

Feather::Feather()
{

}

Feather::~Feather()
{
    CC_SAFE_RELEASE(_mainSprite);
}

bool Feather::init()
{
    if(!Node::init())
        return false;
    
    if(nullptr == _mainSprite)
    {
        _mainSprite = Sprite::create(ResourcePic::FEATHER);
        _mainSprite->retain();
        
        this->addChild(_mainSprite);
    }
    
    return true;
}

Size Feather::getFeatherSize()
{
    Size size(0, 0);
    if(_mainSprite)
    {
        size = _mainSprite->getContentSize();
    }
    
    return size;
}