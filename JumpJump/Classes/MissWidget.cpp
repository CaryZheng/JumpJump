//
//  MissWidget.cpp
//  JumpJump
//
//  Created by Cary Zheng on 14-3-27.
//
//

#include "MissWidget.h"
#include "ResourceStrings.h"

USING_NS_CC;

bool MissWidget::init()
{
    if(!Node::init())
        return false;
    
    return true;
}

void MissWidget::addMissItem()
{
    float offsetX = 20.0f;
    
    auto missItem = Sprite::create(ResourcePic::MISS_ITEM);
    missItem->setAnchorPoint(Point(0, 1.0f));
    float missItemWidth = missItem->getContentSize().width;
    
    if(0 == getMissItemNum())
        offsetX = 0;
    
    missItem->setPosition(Point(0 + _missItems.size()*missItemWidth + offsetX, 0));
    
    this->addChild(missItem);
    _missItems.pushBack(missItem);
}

int MissWidget::getMissItemNum()
{
    return _missItems.size();
}