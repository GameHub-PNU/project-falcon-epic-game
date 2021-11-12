

#include "MenuScene.h"
#include "ChooseLevelGameScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = MenuScene::create();
    
    scene->addChild(layer);
    
    return scene;

}

// on "init" you need to initialize your instance
bool MenuScene::init()
{

    if (!Scene::init())
    {
        return false;
    }

    auto playMenuItem = MenuItemImage::create("StartButton.png", "StartButton.png", CC_CALLBACK_1(MenuScene::GoToChooseLevelGameScene, this));
    playMenuItem->setScale(0.7);

    auto menuItems = Menu::create(playMenuItem, NULL);
    menuItems->alignItemsVerticallyWithPadding(200);

    this->addChild(menuItems);
    return true;
}
void MenuScene::GoToChooseLevelGameScene(Ref* pSender) {
    auto scene = ChooseLevelGameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
