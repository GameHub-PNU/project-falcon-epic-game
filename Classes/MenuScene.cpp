#include "MenuScene.h"
#include "ChooseLevelGameScene.h"
#include "SettingsScene.h"
#include "AudioEngine.h"
#include "SettingsHandler.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //const float OFFSET = 20.0f;
    background_sprite->setPosition(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 2.0f);
    this->addChild(background_sprite);

    auto exitMenuItem = MenuItemImage::create("EXIT.png", "EXIT.png", CC_CALLBACK_0(MenuScene::ExitFromGame, this));
    exitMenuItem->setScale(0.5f);
    /*exitButton->setPosition(Vec2(exitButton->getContentSize().width * exitButton->getScaleX() / 2.0f + OFFSET,
        Director::getInstance()->getWinSize().height - exitButton->getContentSize().height * exitButton->getScaleX() / 2.0f - OFFSET));*/

    auto playMenuItem = MenuItemImage::create("StartButton.png", "StartButton.png", CC_CALLBACK_1(MenuScene::GoToChooseLevelGameScene, this));
    playMenuItem->setScale(0.7f);

    auto settingsMenuItem = MenuItemImage::create("SettingButton.png", "SettingButton.png", CC_CALLBACK_1(MenuScene::GoToSettingsScene, this));
    settingsMenuItem->setScale(0.5f);

    auto menuItems = Menu::create(exitMenuItem, playMenuItem, settingsMenuItem, NULL);
    
    menuItems->alignItemsHorizontallyWithPadding(30);
    
    this->addChild(menuItems);
    gameName->setPosition(Director::getInstance()->getWinSize().width / 2.0f, 1.70f * menuItems->getPosition().y);

    gameName->enableShadow(Color4B::BLACK, Size(5, -5), 2);

    if (experimental::AudioEngine::getPlayingAudioCount() == 0) {
        soundId = experimental::AudioEngine::play2d("sound.mp3", true, SettingsHandler::getSoundVolume());
        SettingsHandler::setCurrentAudioId(soundId);
    }

    this->addChild(gameName);
    return true;
}

void MenuScene::GoToChooseLevelGameScene(Ref* pSender)
{
    auto scene = ChooseLevelGameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}

void MenuScene::GoToSettingsScene(Ref* pSender)
{
    auto scene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}

void MenuScene::ExitFromGame()
{
    exit(0);
}
