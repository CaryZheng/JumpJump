//
//  GameConfigData.cpp
//  JumpJump
//
//  Created by Cary Zheng on 14-4-1.
//
//

#include "GameConfigData.h"
#include "json.h"
#include "cocos2d.h"

bool GameConfigData::parseConfigFile()
{
    bool ret = false;
    
    std::string strSrc = cocos2d::FileUtils::getInstance()->getStringFromFile("Config.json");
    
    Json::Reader reader;
    Json::Value root;
    if(reader.parse(strSrc, root))
    {
        ret = true;
        
        if(root.isObject())
        {
            Json::Value gameDifficultyObject = root.get("GameDifficulty", Json::Value::null);
            if(gameDifficultyObject.isObject())
            {
                Json::Value::Members member = gameDifficultyObject.getMemberNames();
                for(auto iter = member.begin(); iter != member.end(); iter++)
                {
                    Json::Value levelObject = gameDifficultyObject.get(*iter, Json::Value::null);
                    if(levelObject.isObject())
                    {
                        GameLevel gameLevel;
                        gameLevel.rate2 = levelObject["rate2"].asFloat();
                        gameLevel.rate3 = levelObject["rate3"].asFloat();
                        
                        gameDifficulty.vGameLevels.push_back(gameLevel);
                    }
                }
            }
        }
    }
    
    return ret;
}