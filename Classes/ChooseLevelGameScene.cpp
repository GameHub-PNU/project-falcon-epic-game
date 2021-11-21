#include "ChooseLevelGameScene.h"
#include "FirstLevelGameScene.h"
#include "SecondLevelGameScene.h"
#include "ThirdLevelGameScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* ChooseLevelGameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ChooseLevelGameScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool ChooseLevelGameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    background_sprite->setPosition(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 2.0f);
    this->addChild(background_sprite);

    auto firstLevelMenuItem = MenuItemImage::create("LevelOne.png", "LevelOne.png", CC_CALLBACK_1(ChooseLevelGameScene::GoToFirstLevelGameScene, this));
    auto secondLevelMenuItem = MenuItemImage::create("LevelTwo.png", "LevelTwo.png", CC_CALLBACK_1(ChooseLevelGameScene::GoToSecondLevelGameScene, this));
    auto thirdLevelMenuItem = MenuItemImage::create("LevelThree.png", "LevelThree.png", CC_CALLBACK_1(ChooseLevelGameScene::GoToThirdLevelGameScene, this));

    auto menuItems = Menu::create(firstLevelMenuItem, secondLevelMenuItem, thirdLevelMenuItem, NULL);
    menuItems->alignItemsVerticallyWithPadding(40);

    auto backToMenuItem = MenuItemImage::create("Back.png", "Back.png", CC_CALLBACK_1(ChooseLevelGameScene::GoToMenuScene, this));
    auto exitMenu = Menu::create(backToMenuItem, NULL);
    exitMenu->setScale(0.3);
    exitMenu->setAnchorPoint(Vec2(0, 0));
    exitMenu->setPosition(Vec2(65, 725));
    

    this->addChild(exitMenu);
    this->addChild(menuItems);

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


void ChooseLevelGameScene::GoToMenuScene(Ref* pSender) {
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5,scene));
}