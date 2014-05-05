#include "AppDelegate.h"
#include "StartLayer.h"
#include "GameLogicManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceStrings.h"
#include "GameDataManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
    director->setOpenGLView(glview);
    
    auto screenSize = glview->getFrameSize();
    auto designSize = Size(320.0f, 480.0f);
    std::vector<std::string> searchPaths;

    // 目前只用hd一套素材
    searchPaths.push_back("hd");
    searchPaths.push_back("music");
    director->setContentScaleFactor(640.0f/designSize.width);
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
	
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(ResourceMusic::GAME_BGM);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(ResourceMusic::GET_FEATHER);
    
    GameDataManager::getInstance()->loadConfigFile();
    
    GameLogicManager::getInstance()->enterStartScene();
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
