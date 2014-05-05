//
//  GameLogicManager.h
//  JumpJump
//
//  Created by Cary Zheng on 14-3-27.
//
//

#ifndef __JumpJump__GameLogicManager__
#define __JumpJump__GameLogicManager__

class GameLogicManager
{
public:
    static GameLogicManager* getInstance();
    
    void enterStartScene();
    void enterGameScene();
    void exitGameScene();
    void enterGameOverScene(int score);
    
private:
    GameLogicManager();
    ~GameLogicManager();
    
private:
    static GameLogicManager* _sharedInstance;
};

#endif /* defined(__JumpJump__GameLogicManager__) */
