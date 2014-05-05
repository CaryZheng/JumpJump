//
//  GameLayer.h
//  JumpJump
//
//  Created by Cary Zheng on 14-3-25.
//
//

#ifndef __JumpJump__GameLayer__
#define __JumpJump__GameLayer__

#include "cocos2d.h"
#include "Player.h"
#include "Feather.h"
#include "UIText.h"
#include "MissWidget.h"

class GameLayer : public cocos2d::Layer
{
public:
    GameLayer();
    ~GameLayer();
    
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameLayer);
    
    virtual bool init();
    
    void setPhyWorld(cocos2d::PhysicsWorld* world)
    {
        _world = world;
    }
    
    virtual void update(float delta) override;
    
private:
    void removeFeather(Feather* object);
    void handleLevel();
    
private:
    Player* _player = nullptr;
    cocos2d::Vector<Feather*> _feathers;
    cocos2d::PhysicsWorld* _world = nullptr;
    bool _isGameOver = false;
    cocos2d::ui::Text* _scoreText = nullptr;
    int _score = 0;
    MissWidget* _missWidget = nullptr;
    int _gameLevel = 1;
    bool _isGameBkgChanged = false;
    
    cocos2d::Point _originPos;
    cocos2d::Point _desPos;
};

#endif /* defined(__JumpJump__GameLayer__) */
