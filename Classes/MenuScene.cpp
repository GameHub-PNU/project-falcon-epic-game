#include "MenuScene.h"
#include "ChooseLevelGameScene.h"
#include "SettingsScene.h"
#include "AudioEngine.h"
#include "SettingsHandler.h"
#include "network/HttpRequest.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

void MenuScene::addBackgroundAnimation()
{
    for (int i = 1; i <= 8; i++) {
        std::string name = StringUtils::format("Backgrounds/background%003d.png", i);
        background_animation_->addSpriteFrameWithFile(name);
    }
    background_animation_->setDelayPerUnit(3.75f);
    background_animation_->setLoops(-1);
}

void MenuScene::departmentButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::ENDED)
        Application::getInstance()->openURL("https://comp-sc.pnu.edu.ua/");
}

void MenuScene::gameHubButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::ENDED)
        Application::getInstance()->openURL("https://comp-sc.pnu.edu.ua/gamehubpnu/");
}

bool MenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    addBackgroundAnimation();

    background_sprite_->setPosition(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 2.0f);
    this->addChild(background_sprite_);

    auto exitMenuItem = MenuItemImage::create("EXIT.png", "EXIT.png", CC_CALLBACK_0(MenuScene::exitFromGame, this));
    exitMenuItem->setScale(0.5f);

    auto playMenuItem = MenuItemImage::create("StartButton.png", "StartButton.png", CC_CALLBACK_1(MenuScene::goToChooseLevelGameScene, this));
    playMenuItem->setScale(0.7f);

    auto settingsMenuItem = MenuItemImage::create("SettingButton.png", "SettingButton.png", CC_CALLBACK_1(MenuScene::goToSettingsScene, this));
    settingsMenuItem->setScale(0.5f);

    auto menuItems = Menu::create(exitMenuItem, playMenuItem, settingsMenuItem, NULL);
    
    menuItems->alignItemsHorizontallyWithPadding(30);
    
    this->addChild(menuItems);
    game_name_->setPosition(Director::getInstance()->getWinSize().width / 2.0f, 1.6f * menuItems->getPosition().y);

    game_name_->enableShadow(Color4B::BLACK, Size(5, -5), 2);

    department_button_->setPosition(Vec2(0.89f * Director::getInstance()->getWinSize().width, 0.12f * Director::getInstance()->getWinSize().height));
    department_button_->setScale(0.6f);
    department_button_->addTouchEventListener(CC_CALLBACK_2(MenuScene::departmentButtonClicked, this));
    this->addChild(department_button_);

    gameHub_button_->setPosition(Vec2(0.1f * Director::getInstance()->getWinSize().width, 0.11f * Director::getInstance()->getWinSize().height));
    gameHub_button_->setScale(0.6f);
    gameHub_button_->addTouchEventListener(CC_CALLBACK_2(MenuScene::gameHubButtonClicked, this));
    this->addChild(gameHub_button_);

    if (experimental::AudioEngine::getPlayingAudioCount() == 0) {
        sound_id_ = experimental::AudioEngine::play2d("sound.mp3", true, SettingsHandler::getSoundVolume());
        SettingsHandler::setCurrentAudioId(sound_id_);
    }

    this->addChild(game_name_);
    
    background_sprite_->runAction(Animate::create(background_animation_));

    return true;
}

void MenuScene::goToChooseLevelGameScene(Ref* pSender)
{
    auto scene = ChooseLevelGameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}

void MenuScene::goToSettingsScene(Ref* pSender)
{
    auto scene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}

void MenuScene::exitFromGame()
{
    experimental::AudioEngine::end();
    exit(0);
}
