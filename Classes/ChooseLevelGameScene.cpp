#include "ChooseLevelGameScene.h"
#include"FirstLevelGameScene.h"
#include"SecondLevelGameScene.h"
#include"ThirdLevelGameScene.h"
USING_NS_CC;

Scene* ChooseLevelGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = ChooseLevelGameScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;

}

// on "init" you need to initialize your instance
bool ChooseLevelGameScene::init()
{

    if (!Scene::init())
    {
        return false;
    }

    return true;
}
void ChooseLevelGameScene::GoToFirstLevelGameScene(Ref* pSender) {
    auto scene = FirstLevelGameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
void ChooseLevelGameScene::GoToSecondLevelGameScene(Ref* pSender) {
    auto scene = SecondLevelGameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
void ChooseLevelGameScene::GoToThirdLevelGameScene(Ref* pSender) {
    auto scene = ThirdLevelGameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

