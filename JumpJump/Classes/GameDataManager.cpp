//
//  GameDataManager.cpp
//  JumpJump
//
//  Created by Cary Zheng on 14-3-27.
//
//

#include "GameDataManager.h"

USING_NS_CC;

GameDataManager* GameDataManager::_sharedInstance = nullptr;

GameDataManager::GameDataManager()
{
    _bestScore = UserDefault::getInstance()->getIntegerForKey(KEY_BEST_SCORE, 0);
}

GameDataManager::~GameDataManager()
{
    if(_pGameConfigData)
        delete _pGameConfigData;
}

GameDataManager* GameDataManager::getInstance()
{
    if(nullptr == _sharedInstance)
        _sharedInstance = new GameDataManager();
    
    return _sharedInstance;
}

void GameDataManager::loadConfigFile()
{
    if(nullptr == _pGameConfigData)
        _pGameConfigData = new GameConfigData();
        
    _pGameConfigData->parseConfigFile();
}