#include "PauseGameScene.h"

USING_NS_CC;

Scene* PauseGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = PauseGameScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;

}

// on "init" you need to initialize your instance
bool PauseGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    return true;
}

void PauseGameScene::ResumeGame(Ref* pSender) {
    /*auto scene = ChooseLevelGameScene::createScene();
    Director::getInstance()->replaceScene(scene);*/
    Director::getInstance()->popScene();
}