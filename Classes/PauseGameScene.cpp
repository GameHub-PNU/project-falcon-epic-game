#include "PauseGameScene.h"
#include "MenuScene.h"

#include "FirstLevelGameScene.h"
#include "SecondLevelGameScene.h"
#include "ThirdLevelGameScene.h"

#include "AudioEngine.h"
#include "SettingsHandler.h"
USING_NS_CC;

int PauseGameScene::_levelStatus = 0;

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
    _levelStatus = levelStatus;
    return createScene();
}

// on "init" you need to initialize your instance
bool PauseGameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    background_sprite->setPosition(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 2.0f);
    this->addChild(background_sprite);

    auto resumeMenuItem = MenuItemImage::create("RESUME.png", "RESUME.png", CC_CALLBACK_1(PauseGameScene::ResumeGame, this));
    resumeMenuItem->setScale(0.6f);
    auto restartMenuItem = MenuItemImage::create("RESTART.png", "RESTART.png", CC_CALLBACK_1(PauseGameScene::RestartGame, this));
    restartMenuItem->setScale(0.6f);
    auto exitMenuItem = MenuItemImage::create("MENU.png", "MENU.png", CC_CALLBACK_1(PauseGameScene::GoToMenuScene, this));
    exitMenuItem->setScale(0.6f);
    
    auto MenuItems = Menu::create(resumeMenuItem, restartMenuItem, exitMenuItem, NULL);
    MenuItems->alignItemsVerticallyWithPadding(30);
    this->addChild(MenuItems);

    return true;
}

void PauseGameScene::ResumeGame(Ref* pSender) {
    /*auto scene = ChooseLevelGameScene::createScene();
    Director::getInstance()->replaceScene(scene);*/
    experimental::AudioEngine::resumeAll();
    Director::getInstance()->popScene();
}

void PauseGameScene::RestartGame(Ref* pSender)
{
    experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
    if (PauseGameScene::_levelStatus == 1) {
        auto scene = FirstLevelGameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    if (PauseGameScene::_levelStatus == 2) {
        auto scene = SecondLevelGameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    if (PauseGameScene::_levelStatus == 3) {
        auto scene = ThirdLevelGameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}

void PauseGameScene::GoToMenuScene(Ref* pSender)
{
    experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
