#include "SecondLevelGameScene.h"

#include "CCVideoManager.h"
#include "PauseGameScene.h"

USING_NS_CC;

Scene* SecondLevelGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = SecondLevelGameScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;

}

// on "init" you need to initialize your instance
bool SecondLevelGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    /*CCVideoManager::Instance()->PlayVideo("end1.m4v");*/
    return true;
}
void SecondLevelGameScene::GoToPauseScene(Ref* pSender) {
    auto scene = PauseGameScene::createScene();
    Director::getInstance()->pushScene(scene);
}