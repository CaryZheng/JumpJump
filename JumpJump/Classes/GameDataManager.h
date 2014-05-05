//
//  GameDataManager.h
//  JumpJump
//
//  Created by Cary Zheng on 14-3-27.
//
//

#ifndef __JumpJump__GameDataManager__
#define __JumpJump__GameDataManager__

#include "TypeDefine.h"
#include "GameConfigData.h"
#include "cocos2d.h"

#define KEY_BEST_SCORE  "key_best_score"

class GameDataManager
{
public:
    static GameDataManager* getInstance();
    
    GameDataManager();
    ~GameDataManager();
    
public:
    void setGameState(GameState gameState){_gameState = gameState;}
    GameState getGameState(){return _gameState;}
    void setBestScore(int bestScore)
    {
        _bestScore = bestScore;
        cocos2d::UserDefault::getInstance()->setIntegerForKey(KEY_BEST_SCORE, _bestScore);
    }
    int getBestScore(){return _bestScore;}
    
    void loadConfigFile();
    GameConfigData* getGameConfigData(){return _pGameConfigData;}
    
private:
    static GameDataManager* _sharedInstance;
    
    GameState _gameState = GAME_NONE;
    GameConfigData* _pGameConfigData = nullptr;
    int _bestScore = 0;
};

#endif /* defined(__JumpJump__GameDataManager__) */
