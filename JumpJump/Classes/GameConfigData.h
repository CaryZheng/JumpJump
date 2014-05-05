//
//  GameConfigData.h
//  JumpJump
//
//  Created by Cary Zheng on 14-4-1.
//
//

#ifndef __JumpJump__GameConfigData__
#define __JumpJump__GameConfigData__

#include <vector>

class GameConfigData
{
public:
    GameConfigData(){}
    ~GameConfigData(){}
    
public:
    bool parseConfigFile();
    
public:
    typedef struct GameLevelStruct
    {
        GameLevelStruct()
        {
            rate2 = 0;
            rate3 = 0;
        }
        
        float rate2;        // 产生2片羽毛的概率
        float rate3;        // 产生3片羽毛的概率
    }GameLevel;
    
    typedef struct GameDifficultyStruct
    {
        typedef std::vector<GameLevel> GameLevels;
        GameLevels vGameLevels;
    }GameDifficulty;
    
    GameDifficulty gameDifficulty;
};

#endif /* defined(__JumpJump__GameConfigData__) */
