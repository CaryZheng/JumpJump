//
//  GameLayer.cpp
//  JumpJump
//
//  Created by Cary Zheng on 14-3-25.
//
//

#include "GameLayer.h"
#include "GlobalUtility.h"
#include "GameLogicManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceStrings.h"
#include "GameDataManager.h"

USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;

#define GAME_DEBUG false

const int ZORDER_PLAYER = 1;
const int ZORDER_FEATHER = 2;
const int ZORDER_SCORE_TEXT = 10;
const int ZORDER_MISS_WIDGET = 11;

const int BODY_COLLISION_GROUP = 100;
const int BODY_UNCOLLISION_GROUP = -1;

const int TAG_GAME_BKG = 1000;

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{
    CC_SAFE_RELEASE(_player);
    CC_SAFE_RELEASE(_scoreText);
    CC_SAFE_RELEASE(_missWidget);
}

Scene* GameLayer::createScene()
{
    auto scene = Scene::createWithPhysics();
    
    if(GAME_DEBUG)
        scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = GameLayer::create();
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto edgeLeftBody = PhysicsBody::createEdgeSegment(Point(0, 0), Point(0, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeLeftBody->setGroup(BODY_COLLISION_GROUP);
    auto edgeLeftNode = Node::create();
    edgeLeftNode->setPosition(Point(origin.x, origin.y));
    edgeLeftNode->setPhysicsBody(edgeLeftBody);
    scene->addChild(edgeLeftNode);
    
    auto edgeRightBody = PhysicsBody::createEdgeSegment(Point(0, 0), Point(0, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeRightBody->setGroup(BODY_COLLISION_GROUP);
    auto edgeRightNode = Node::create();
    edgeRightNode->setPosition(Point(origin.x + visibleSize.width, origin.y));
    edgeRightNode->setPhysicsBody(edgeRightBody);
    scene->addChild(edgeRightNode);
    
    auto edgeTopBody = PhysicsBody::createEdgeSegment(Point(0, 0), Point(visibleSize.width, 0), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeTopBody->setGroup(BODY_COLLISION_GROUP);
    auto edgeTopNode = Node::create();
    edgeTopNode->setPosition(Point(origin.x, origin.y + visibleSize.height));
    edgeTopNode->setPhysicsBody(edgeTopBody);
    scene->addChild(edgeTopNode);
    
    return scene;
}

bool GameLayer::init()
{
    if(!Layer::init())
        return false;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    if(!GAME_DEBUG)
    {
        auto bkg = Sprite::create(ResourcePic::GAME_BKG);
        bkg->setTag(TAG_GAME_BKG);
        bkg->setAnchorPoint(Point(0.5f, 0.5f));
        bkg->setPosition(Point(origin.x + visibleSize.width/2.0f, origin.y + visibleSize.height/2.0f));
        this->addChild(bkg);
    }
    
    _missWidget = MissWidget::create();
    _missWidget->retain();
    _missWidget->setPosition(Point(origin.x + 20.0f, origin.y + visibleSize.height - 20.0f));
    _missWidget->addMissItem();
    this->addChild(_missWidget, ZORDER_MISS_WIDGET);
    
    _scoreText = Text::create();
    _scoreText->retain();
    _scoreText->setFontSize(40.0f);
    _scoreText->setText(GlobalUtility::toString(_score));
    _scoreText->setPosition(Point(origin.x + visibleSize.width* 5.0f/6.0f, origin.y + visibleSize.height*1.0f/10.0f));
    this->addChild(_scoreText, ZORDER_SCORE_TEXT);
    
    auto player = Player::create();
    _player = player;
    _player->retain();
    player->setAnchorPoint(Point(0.5f, 0.5f));
    player->setPosition(Point(origin.x + visibleSize.width/2.0f, origin.y + visibleSize.height/2.0f));
    
    auto playerBody = PhysicsBody::createCircle(35.0f);
    playerBody->setGroup(BODY_COLLISION_GROUP);
    player->setPhysicsBody(playerBody);
    
    this->addChild(player, ZORDER_PLAYER);

//    auto bodyContactListener = EventListenerPhysicsContactWithGroup::create(BODY_UNCOLLISION_GROUP);
//    bodyContactListener->onContactBegin = [](PhysicsContact& contact){
//        
//        CCLOG("BODY_UNCOLLISION_GROUP onContactBegin");
//        
//        return false;
//    };
//    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(bodyContactListener, this);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [this, player](Touch* touch, Event* event){
        
        Point visibleOrigin = Director::getInstance()->getVisibleOrigin();
        Size visibleSize = Director::getInstance()->getVisibleSize();
        
        Point playerPos = player->getPosition();
        Point touchPos = Point(touch->getLocationInView().x, visibleSize.height - touch->getLocationInView().y);
        
        for(int i = 0; i < _feathers.size();)
        {
            Feather* feather = _feathers.at(i);
            Size featherSize = feather->getFeatherSize();
            Point featherPos = feather->getPosition();
            float featherLeft = featherPos.x - feather->getAnchorPoint().x*featherSize.width;
            float featherBottom = featherPos.y - feather->getAnchorPoint().y*featherSize.height;
            Rect featherRect(featherLeft, featherBottom, featherSize.width, featherSize.height);
            if(featherRect.containsPoint(touchPos))
            {
                SimpleAudioEngine::getInstance()->playEffect(ResourceMusic::GET_FEATHER);
                
                this->removeFeather(feather);
                _score++;
                
                this->handleLevel();
                
                continue;
            }
            
            i++;
        }
        
        auto playerSize = player->getPlayerSize();
        
        float playerLeft = playerPos.x - player->getAnchorPoint().x * playerSize.width;
//        float playerMid = playerLeft + playerSize.width/2.0f;
        float playerRight = playerLeft + playerSize.width;
        float playerBottom = playerPos.y - player->getAnchorPoint().y * playerSize.height;
        
        const float offsetX = 10.0f;
        const float offsetY = 30.0f;
        
        Rect rect(playerLeft, playerBottom, playerSize.width, playerSize.height);
        
        Vect vect(0, 0);
        if(fabsf(touchPos.y - playerBottom) <= offsetY || rect.containsPoint(touchPos))
        {
            if(touchPos.x >= playerLeft-offsetX && touchPos.x <= playerRight+offsetX)
            {
                int gameLevel = _gameLevel;
                float rate2 = 0;
                float rate3 = 0;
                float playerVelIncreasePer = (gameLevel - 1) / 100.0f;
                if(playerVelIncreasePer > 1.0f)
                    playerVelIncreasePer = 1.0f;
                
                GameConfigData* pGameConfigData = GameDataManager::getInstance()->getGameConfigData();
                int gameLevelsSize = pGameConfigData->gameDifficulty.vGameLevels.size();
                
                if(gameLevel >= gameLevelsSize && !_isGameBkgChanged)
                {
                    auto child = (Sprite*)this->getChildByTag(TAG_GAME_BKG);
                    if(child)
                    {
                        auto func = [this](Node*){
                            auto child = (Sprite*)this->getChildByTag(TAG_GAME_BKG);
                            if(child)
                            {
                                child->setTexture(ResourcePic::GAME_BKG_2);
                            }
                        };
                        child->runAction(Sequence::create(FadeOut::create(1.0f), CallFuncN::create(func), FadeIn::create(1.0f), NULL));
                        
                        _isGameBkgChanged = true;
                    }
                }
                
                int index = 0;
                if(gameLevel < gameLevelsSize)
                {
                    index = gameLevel - 1;
                }
                else
                {
                    index = gameLevelsSize - 1;
                }
                
                const GameConfigData::GameLevel& gameLevelData = pGameConfigData->gameDifficulty.vGameLevels[index];
                rate2 = gameLevelData.rate2;
                rate3 = gameLevelData.rate3;
                
                int num = 1;
                srand(time(NULL));
                float randomNumPercent = (rand() % 100 + 1) / 100.0f;
                if(randomNumPercent <= rate3)
                {
                    num = 3;
                }
                else if(randomNumPercent <= rate3 + rate2)
                {
                    num = 2;
                }
                else
                {
                    num = 1;
                }
                
                float velFactor = 12.0f;
                
                Point offsetPos = playerPos - touchPos;
                vect = offsetPos;
                vect = vect * velFactor * (1 + playerVelIncreasePer);
                
//                CCLOG("onTouchBegan test vect = (%f, %f)", vect.x, vect.y);
                player->getPhysicsBody()->setVelocity(vect);
                
                for(int i = 0; i < num; i++)
                {
                    float featherX = playerPos.x + i*40.0f;
                    if(featherX <= visibleOrigin.x || featherX >= visibleOrigin.x + visibleSize.width)
                        continue;
                    
                    auto feather = Feather::create();
                    feather->setAnchorPoint(Point(0.5f, 0.5f));
                    
                    Point featherPos = Point(featherX, playerPos.y - i*20.0f);
                    feather->setPosition(featherPos);
                    
                    auto featherBody = PhysicsBody::createCircle(10.0f);
                    featherBody->setGroup(BODY_UNCOLLISION_GROUP);
                    featherBody->setCollisionBitmask(0);
                    feather->setPhysicsBody(featherBody);
                    Vect featherVect(0, 10.0f);
                    featherVect = featherVect * velFactor;
                    feather->getPhysicsBody()->setVelocity(featherVect);
                    
                    this->addChild(feather, ZORDER_FEATHER);
                    
                    _feathers.pushBack(feather);
                }
                
                _originPos.x = playerLeft - offsetX;
                _originPos.y = playerBottom - offsetY;
                _desPos.x = playerRight + offsetX;
                _desPos.y = playerBottom + offsetY;
            }
        }
        
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    this->scheduleUpdate();
    
    return true;
}

void GameLayer::update(float delta)
{
    if(_isGameOver)
        return;
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // remove feathers
    for(int i = 0; i < _feathers.size();)
    {
        Feather* feather = _feathers.at(i);
        auto featherPos = feather->getPosition();
        if(featherPos.y < origin.y)
        {
            removeFeather(feather);
            
            if(_missWidget->getMissItemNum() < 2)
                _missWidget->addMissItem();
            else
                _isGameOver = true;
            
            continue;
        }
        
        i++;
    }
    
    auto playerPos = _player->getPosition();
    if(playerPos.y < origin.y)
    {
        CCLOG("Game Over");
        
        _isGameOver = true;
    }
    
    _scoreText->setText(GlobalUtility::toString(_score));
    
    if(_isGameOver)
    {
        if(_score > GameDataManager::getInstance()->getBestScore())
        {
            GameDataManager::getInstance()->setBestScore(_score);
        }
        
        GameLogicManager::getInstance()->exitGameScene();
        GameLogicManager::getInstance()->enterGameOverScene(_score);
    }
}

void GameLayer::removeFeather(Feather* object)
{
    _feathers.eraseObject(object);
    this->removeChild(object);
}

void GameLayer::handleLevel()
{
    int gameLevel = 1;
    if(_score >= 0)
    {
        gameLevel = _score / 10 + 1;
    }
    
    _gameLevel = gameLevel;
}