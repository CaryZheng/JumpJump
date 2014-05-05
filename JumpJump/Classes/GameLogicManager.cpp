//
//  GameLogicManager.cpp
//  JumpJump
//
//  Created by Cary Zheng on 14-3-27.
//
//

#include "GameLogicManager.h"
#include "cocos2d.h"
#include "GameLayer.h"
#include "GameOverLayer.h"
#include "StartLayer.h"
#include "GameDataManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceStrings.h"

USING_NS_CC;
using namespace CocosDenshion;

GameLogicManager* GameLogicManager::_sharedInstance = nullptr;

GameLogicManager* GameLogicManager::getInstance()
{
    if(nullptr == _sharedInstance)
        _sharedInstance = new GameLogicManager();
    
    return _sharedInstance;
}

GameLogicManager::GameLogicManager()
{

}

GameLogicManager::~GameLogicManager()
{

}

void GameLogicManager::enterStartScene()
{
    GameDataManager::getInstance()->setGameState(GAME_START);
    
    auto director = Director::getInstance();
    auto scene = StartLayer::createScene();
    
    if(director->getRunningScene())
        director->replaceScene(scene);
    else
        director->runWithScene(scene);
}

void GameLogicManager::enterGameScene()
{
    GameDataManager::getInstance()->setGameState(GAME_PLAY);
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic(ResourceMusic::GAME_BGM);
    
    auto director = Director::getInstance();
    auto scene = GameLayer::createScene();
    director->replaceScene(scene);
}

void GameLogicManager::exitGameScene()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->stopAllEffects();
}

void GameLogicManager::enterGameOverScene(int score)
{
    GameDataManager::getInstance()->setGameState(GAME_OVER);
    
    auto director = Director::getInstance();
    auto scene = GameOverLayer::createScene(score);
    director->replaceScene(scene);
}