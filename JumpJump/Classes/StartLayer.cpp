//
//  StartLayer.cpp
//  JumpJump
//
//  Created by Cary Zheng on 14-3-25.
//
//

#include "StartLayer.h"
#include "GameLogicManager.h"
#include "ResourceStrings.h"

USING_NS_CC;
using namespace ui;

Scene* StartLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = StartLayer::create();
    scene->addChild(layer);

    return scene;
}

bool StartLayer::init()
{
    if(!Layer::init())
        return false;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto bkg = Sprite::create(ResourcePic::START_BKG);
    bkg->setAnchorPoint(Point(0.5f, 0.5f));
    bkg->setPosition(Point(origin.x + visibleSize.width/2.0f, origin.y + visibleSize.height/2.0f));
    this->addChild(bkg);

    auto startButton = Button::create();
    startButton->setTouchEnabled(true);
    startButton->loadTextureNormal(ResourcePic::START_BUTTON);
    startButton->setAnchorPoint(Point(0.5f, 0.5f));
    startButton->setPosition(Point(origin.x + visibleSize.width/2.0f, origin.y + visibleSize.height/2.0f));
    startButton->addTouchEventListener(this, toucheventselector(StartLayer::onClickStartButton));
    this->addChild(startButton);
    
    return true;
}

void StartLayer::onClickStartButton(Ref* object, TouchEventType type)
{
    if(TOUCH_EVENT_ENDED == type)
    {
        GameLogicManager::getInstance()->enterGameScene();
    }
}