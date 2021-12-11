#include "GameOverScene.h"
#include "CCVideoManager.h"
#include "AudioEngine.h"
#include "SettingsHandler.h"

#include "FirstLevelGameScene.h"
#include "SecondLevelGameScene.h"
#include "ThirdLevelGameScene.h"

#include "MenuScene.h"
USING_NS_CC;

int GameOverScene::current_progress_ = 0;
int GameOverScene::level_status_ = 0;

Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

Scene* GameOverScene::createScene(int progress_percent, int levelStatus)
{
    current_progress_ = progress_percent;
    level_status_ = levelStatus;
    return createScene();
}

void GameOverScene::checkIfLevelCompleted()
{
    if (current_progress_ == 100)
    {
        roundStatus->setString("You win!");
        CCVideoManager::Instance()->PlayVideo("end1.m4v");
        experimental::AudioEngine::play2d("EndLevelSound.mp3", false, SettingsHandler::getSoundVolume());
    }
    else
    {
        roundStatus->setString("You lose!");
    }
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
    checkIfLevelCompleted();
    

    background_sprite->setPosition(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 2.0f);
    this->addChild(background_sprite);

    auto restartMenuItem = MenuItemImage::create("RESTART.png", "RESTART.png", CC_CALLBACK_1(GameOverScene::RestartGame, this));
    restartMenuItem->setScale(0.6f);
    auto exitMenuItem = MenuItemImage::create("MENU.png", "MENU.png", CC_CALLBACK_1(GameOverScene::GoToMenuScene, this));
    exitMenuItem->setScale(0.6f);
    auto nextLevelItem = MenuItemImage::create("NEXTLEVEL.png", "NEXTLEVEL.png", CC_CALLBACK_1(GameOverScene::GoToNextLevel, this));
    nextLevelItem->setScale(0.6f);

    if (current_progress_ == 100) {
        if (level_status_ != 3) {
            auto MenuItems = Menu::create(nextLevelItem, restartMenuItem, exitMenuItem, NULL);
            MenuItems->alignItemsVerticallyWithPadding(30);
            this->addChild(MenuItems);
            roundStatus->setPosition(Director::getInstance()->getWinSize().width / 2.0f, 1.90f * MenuItems->getPosition().y);
        }
        else {
            auto MenuItems = Menu::create(restartMenuItem, exitMenuItem, NULL);
            MenuItems->alignItemsVerticallyWithPadding(30);
            this->addChild(MenuItems);
            roundStatus->setPosition(Director::getInstance()->getWinSize().width / 2.0f, 1.90f * MenuItems->getPosition().y);
        }
       
    }
    else {
        auto MenuItems = Menu::create(restartMenuItem, exitMenuItem, NULL);
        MenuItems->alignItemsVerticallyWithPadding(40);
        this->addChild(MenuItems);
        roundStatus->setPosition(Director::getInstance()->getWinSize().width / 2.0f, 1.70f * MenuItems->getPosition().y);
    }

    

   
    roundStatus->enableShadow(Color4B::BLACK, Size(5, -5), 2);
    this->addChild(roundStatus);

    return true;
}

void GameOverScene::RestartGame(Ref* pSender)
{
    if (GameOverScene::level_status_ == 1) {
        auto scene = FirstLevelGameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    if (GameOverScene::level_status_ == 2) {
        auto scene = SecondLevelGameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    if (GameOverScene::level_status_ == 3) {
        auto scene = ThirdLevelGameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}

void GameOverScene::GoToMenuScene(Ref* pSender)
{
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GameOverScene::GoToNextLevel(Ref* pSender)
{
    if (GameOverScene::level_status_ == 1) {
        auto scene = SecondLevelGameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    if (GameOverScene::level_status_ == 2) {
        auto scene = ThirdLevelGameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}



