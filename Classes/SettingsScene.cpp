#include "SettingsScene.h"
#include "MenuScene.h"
#include <ui/CocosGUI.h>

USING_NS_CC;

Scene* SettingsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = SettingsScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;

}

// on "init" you need to initialize your instance
bool SettingsScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto background = Sprite::create("SettingsBackground.png");
    background ->setPosition(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 2.0f);
    this->addChild(background);

    auto backToMenuItem = MenuItemImage::create("Back.png", "Back.png", CC_CALLBACK_1(SettingsScene::GoToMenuScene, this));
    auto exitMenu = Menu::create(backToMenuItem, NULL);
    exitMenu->setScale(0.3);
    exitMenu->setAnchorPoint(Vec2(0, 0));
    exitMenu->setPosition(Vec2(65, 725));


    auto slider = ui::Slider::create();
    slider->loadBarTexture("ScrollEmpty.png");
    slider->loadSlidBallTextures("Bar.png");
    slider->loadProgressBarTexture("Scroll.png");
    slider->setScale(2.0);
    slider->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));

    this->addChild(slider);
    
    slider->addEventListener(CC_CALLBACK_2(SettingsScene::buttonClick, this));




    this->addChild(exitMenu);


    return true;
}

void SettingsScene::buttonClick(Ref* pSender, ui::Slider::EventType type)
{
    auto slider = dynamic_cast<ui::Slider*>(pSender);
    if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
        //fly->setScale(slider->getPercent() / 10 + 1);
    }

};


void SettingsScene::GoToMenuScene(Ref* pSender) {
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}