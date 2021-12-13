#include "ChooseLevelGameScene.h"
#include "FirstLevelGameScene.h"
#include "SecondLevelGameScene.h"
#include "ThirdLevelGameScene.h"
#include "MenuScene.h"
#include "AudioEngine.h"
#include "SettingsHandler.h"

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

    background_sprite_->setPosition(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 2.0f);
    this->addChild(background_sprite_);

    auto firstLevelMenuItem = MenuItemImage::create("LevelOne.png", "LevelOne.png", CC_CALLBACK_1(ChooseLevelGameScene::goToFirstLevelGameScene, this));
    auto secondLevelMenuItem = MenuItemImage::create("LevelTwo.png", "LevelTwo.png", CC_CALLBACK_1(ChooseLevelGameScene::goToSecondLevelGameScene, this));
    auto thirdLevelMenuItem = MenuItemImage::create("LevelThree.png", "LevelThree.png", CC_CALLBACK_1(ChooseLevelGameScene::goToThirdLevelGameScene, this));

    auto menuItems = Menu::create(firstLevelMenuItem, secondLevelMenuItem, thirdLevelMenuItem, NULL);
    menuItems->alignItemsVerticallyWithPadding(40);

    auto backToMenuItem = MenuItemImage::create("Back.png", "Back.png", CC_CALLBACK_1(ChooseLevelGameScene::goToMenuScene, this));
    auto exitMenu = Menu::create(backToMenuItem, NULL);
    exitMenu->setScale(0.3f);
    exitMenu->setAnchorPoint(Vec2(0, 0));
    exitMenu->setPosition(Vec2(65, 725));

    this->addChild(exitMenu);
    this->addChild(menuItems);

    return true;
}

void ChooseLevelGameScene::goToFirstLevelGameScene(Ref* pSender) {
    experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
    auto scene = FirstLevelGameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene));
}

void ChooseLevelGameScene::goToSecondLevelGameScene(Ref* pSender) {
    experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
    auto scene = SecondLevelGameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene));
}

void ChooseLevelGameScene::goToThirdLevelGameScene(Ref* pSender) {
    experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
    auto scene = ThirdLevelGameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene));
}


void ChooseLevelGameScene::goToMenuScene(Ref* pSender) {
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}