#include "AppDelegate.h"
#include "BattleScene.h"
#include "define.h"

int GlobalVars::scene_width = 0;
int GlobalVars::scene_height = 0;
BehaviorMode GlobalVars::behavior_mode = BehaviorMode::MANUAL;

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
		
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		glview->setFrameSize(960, 640);
#endif
        director->setOpenGLView(glview);
    }
    
    auto s = glview->getFrameSize();
    GlobalVars::scene_width = s.width;
    GlobalVars::scene_height = s.height;

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	
	//Resolution
	auto screenSize = glview->getFrameSize();
	auto designSize = Size(960, 640);
    auto resourceSize = Size(960, 640);
	
    director->setContentScaleFactor(resourceSize.height/designSize.height);
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);

    // create a scene. it's an autorelease object
    auto scene = BattleScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
