#include "ChooseLevelGameScene.h"
#include "FirstLevelGameScene.h"
#include "SecondLevelGameScene.h"
#include "ThirdLevelGameScene.h"
#include "MenuScene.h"
#include "AudioEngine.h"
#include "SettingsHandler.h"
#include "ui/UIPageView.h"
#include "ui/UILayout.h"
#include "ui/UIImageView.h"
#include <fstream>

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
    getUserRecords();

    background_sprite_->setPosition(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 2.0f);
    this->addChild(background_sprite_);
    Size page_view_size = Size(Director::getInstance()->getWinSize());
    ui::PageView* pageView = ui::PageView::create();
    pageView->setDirection(ui::PageView::Direction::HORIZONTAL);
    pageView->setContentSize(page_view_size);
    pageView->setIndicatorEnabled(true);
    pageView->setIndicatorPosition(Vec2(Director::getInstance()->getWinSize().width / 2.0f, 0.01f * Director::getInstance()->getWinSize().height));
    pageView->setIndicatorSpaceBetweenIndexNodes(50.0f);
    pageView->setIndicatorIndexNodesScale(0.7f);
    for (size_t i = 0; i < SettingsHandler::getMaxProgress().size(); ++i)
    {
        ui::Slider* slider = ui::Slider::create();
        slider->loadBarTexture("slider_back.png");
        slider->loadProgressBarTexture("slider_filled.png");
        slider->setScale(1.15f);
        slider->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2.0f, 0.3f * Director::getInstance()->getWinSize().height));
        slider->setEnabled(false);
        level_progresses_.push_back(slider);
    }

    for (size_t i = 1; i <= SettingsHandler::getMaxProgress().size(); ++i)
    {
	    ui::Layout* layout = ui::Layout::create();
        layout->setContentSize(page_view_size);

        ui::Button* level_button = ui::Button::create(StringUtils::format("LevelButtons/Level%d.png", i));
        level_button->setPosition(Vec2(layout->getContentSize().width / 2.0f, 0.63f * layout->getContentSize().height));
        level_button->setScale(1.3f);
        Label* music_label = Label::createWithSystemFont(StringUtils::format("Music%d", i), "Arial", 30);
        music_label->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2.0f, 0.1f * Director::getInstance()->getWinSize().height));

        percentages_.at(i - 1)->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2.0f, 0.3f * Director::getInstance()->getWinSize().height));
        percentages_.at(i - 1)->setString(std::to_string(SettingsHandler::getMaxProgress().at(i - 1)) + '%');

    	switch (i)
	    {
			case 1: 
                level_button->addTouchEventListener(CC_CALLBACK_2(ChooseLevelGameScene::goToFirstLevelGameScene, this));
                music_label->setString("Music: MaYuL - Sunset Color");
	    		break;
            case 2: 
                level_button->addTouchEventListener(CC_CALLBACK_2(ChooseLevelGameScene::goToSecondLevelGameScene, this));
                music_label->setString("Music: Edith Piaf - Non, Je Ne Regrette Rien");
	    		break;
            case 3: 
                level_button->addTouchEventListener(CC_CALLBACK_2(ChooseLevelGameScene::goToThirdLevelGameScene, this));
                music_label->setString("Music: AC/DC - Highway to Hell");
	    		break;
            default: break;
	    }
        level_progresses_.at(i - 1)->setPercent(SettingsHandler::getMaxProgress().at(i - 1));
        layout->addChild(level_progresses_.at(i - 1));
        layout->addChild(percentages_.at(i - 1));
        layout->addChild(level_button);
        layout->addChild(music_label);
        pageView->addPage(layout);
    }
    this->addChild(pageView);

    auto backToMenuItem = MenuItemImage::create("Back.png", "Back.png", CC_CALLBACK_1(ChooseLevelGameScene::goToMenuScene, this));
    auto exitMenu = Menu::create(backToMenuItem, NULL);
    exitMenu->setScale(0.3f);
    exitMenu->setAnchorPoint(Vec2(0, 0));
    exitMenu->setPosition(Vec2(65, 725));

    this->addChild(exitMenu);

    return true;
}

void ChooseLevelGameScene::getUserRecords()
{
    SettingsHandler::getMaxProgress().clear();
	std::string number;
    std::ifstream records("Backup/records.txt");
    while (std::getline(records, number))
    {
        SettingsHandler::getMaxProgress().push_back(std::stoi(number));
    }
    records.close();
}

void ChooseLevelGameScene::goToFirstLevelGameScene(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::ENDED)
    {
        experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
        auto scene = FirstLevelGameScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene));
    }
}

void ChooseLevelGameScene::goToSecondLevelGameScene(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::ENDED)
    {
        experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
        auto scene = SecondLevelGameScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene));
    }
}

void ChooseLevelGameScene::goToThirdLevelGameScene(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::ENDED)
    {
        experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
        auto scene = ThirdLevelGameScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene));
    }
}

void ChooseLevelGameScene::goToMenuScene(Ref* pSender)
{
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}