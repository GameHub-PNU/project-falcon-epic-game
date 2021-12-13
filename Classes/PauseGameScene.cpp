#include "PauseGameScene.h"
#include "MenuScene.h"

#include "FirstLevelGameScene.h"
#include "SecondLevelGameScene.h"
#include "ThirdLevelGameScene.h"

#include "AudioEngine.h"
#include "SettingsHandler.h"

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

cocos2d::Scene* PauseGameScene::createScene(int levelStatus)
{
    level_status_ = levelStatus;
    return createScene();
}

// on "init" you need to initialize your instance
bool PauseGameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    background_sprite_->setPosition(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 2.0f);
    this->addChild(background_sprite_);

    auto resumeMenuItem = MenuItemImage::create("RESUME.png", "RESUME.png", CC_CALLBACK_1(PauseGameScene::resumeGame, this));
    resumeMenuItem->setScale(0.6f);
    auto restartMenuItem = MenuItemImage::create("RESTART.png", "RESTART.png", CC_CALLBACK_1(PauseGameScene::restartGame, this));
    restartMenuItem->setScale(0.6f);
    auto exitMenuItem = MenuItemImage::create("MENU.png", "MENU.png", CC_CALLBACK_1(PauseGameScene::goToMenuScene, this));
    exitMenuItem->setScale(0.6f);
    
    auto MenuItems = Menu::create(resumeMenuItem, restartMenuItem, exitMenuItem, NULL);
    MenuItems->alignItemsVerticallyWithPadding(30);
    this->addChild(MenuItems);

    return true;
}

void PauseGameScene::resumeGame(Ref* pSender) {
    experimental::AudioEngine::resumeAll();
    Director::getInstance()->popScene();
}

void PauseGameScene::restartGame(Ref* pSender)
{
    experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
    Scene* scene = nullptr;
    switch (level_status_)
    {
    case 1: scene = FirstLevelGameScene::createScene(); break;
    case 2: scene = SecondLevelGameScene::createScene(); break;
    case 3: scene = ThirdLevelGameScene::createScene(); break;
    default: break;
    }
    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene));
}

void PauseGameScene::goToMenuScene(Ref* pSender)
{
    experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}
