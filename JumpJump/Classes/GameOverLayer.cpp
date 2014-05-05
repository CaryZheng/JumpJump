//
//  GameOverLayer.cpp
//  JumpJump
//
//  Created by Cary Zheng on 14-3-27.
//
//

#include "GameOverLayer.h"
#include "GameLogicManager.h"
#include "ResourceStrings.h"
#include "UIText.h"
#include "GlobalUtility.h"

USING_NS_CC;
using namespace ui;

Scene* GameOverLayer::createScene(int score)
{
    auto scene = Scene::create();
    auto layer = GameOverLayer::create(score);
    scene->addChild(layer);
    
    return scene;
}

GameOverLayer* GameOverLayer::create(int score)
{
    GameOverLayer* pRet = new GameOverLayer();
    if(pRet && pRet->init(score))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool GameOverLayer::init(int score)
{
    if(!Layer::init())
        return false;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto bkg = Sprite::create(ResourcePic::GAMEOVER_BKG);
    bkg->setAnchorPoint(Point(0.5f, 0.5f));
    bkg->setPosition(Point(origin.x + visibleSize.width/2.0f, origin.y + visibleSize.height/2.0f));
    this->addChild(bkg);
    
    auto scoreText = Text::create();
    scoreText->retain();
    scoreText->setFontSize(40.0f);
    scoreText->setText(GlobalUtility::toString(score));
    scoreText->setPosition(Point(origin.x + visibleSize.width* 2.0f/3.0f, origin.y + 230.0f));
    this->addChild(scoreText);
    
    auto mainMenuButton = Button::create();
    mainMenuButton->setTouchEnabled(true);
    mainMenuButton->loadTextureNormal(ResourcePic::MAINMENU_BUTTON);
    mainMenuButton->setAnchorPoint(Point(0.5f, 0.5f));
    mainMenuButton->setPosition(Point(origin.x + visibleSize.width*1.0f/4.0f, origin.y + visibleSize.height/6.0f));
    mainMenuButton->addTouchEventListener(this, toucheventselector(GameOverLayer::onClickMainMenuButton));
    this->addChild(mainMenuButton);
    
    auto restartButton = Button::create();
    restartButton->setTouchEnabled(true);
    restartButton->loadTextureNormal(ResourcePic::RETRY_BUTTON);
    restartButton->setAnchorPoint(Point(0.5f, 0.5f));
    restartButton->setPosition(Point(origin.x + visibleSize.width*3.0f/4.0f, origin.y + visibleSize.height/6.0f));
    restartButton->addTouchEventListener(this, toucheventselector(GameOverLayer::onClickRestartButton));
    this->addChild(restartButton);
    
    return true;
}

void GameOverLayer::onClickMainMenuButton(cocos2d::Ref* object, cocos2d::ui::TouchEventType type)
{
    if(TOUCH_EVENT_ENDED == type)
    {
        GameLogicManager::getInstance()->enterStartScene();
    }
}

void GameOverLayer::onClickRestartButton(cocos2d::Ref* object, cocos2d::ui::TouchEventType type)
{
    if(TOUCH_EVENT_ENDED == type)
    {
        GameLogicManager::getInstance()->enterGameScene();
    }
}