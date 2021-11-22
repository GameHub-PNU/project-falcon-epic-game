#include "FirstLevelGameScene.h"
#include "PauseGameScene.h"

USING_NS_CC;

Scene* FirstLevelGameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = FirstLevelGameScene::create();
    scene->addChild(layer);
    return scene;
}

void FirstLevelGameScene::init_listener()
{
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(FirstLevelGameScene::onMouseDown, this);
    listener->onMouseUp = CC_CALLBACK_1(FirstLevelGameScene::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    isGameStarted = true;
}

// on "init" you need to initialize your instance
bool FirstLevelGameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    background_sprite->setPosition(0.0f, Director::getInstance()->getWinSize().height / 2.0f);
    background_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->addChild(background_sprite);
    plane_sprite->setPosition(-2.0f * plane_sprite->getContentSize().width, Director::getInstance()->getWinSize().height / 2.0f);
    this->addChild(plane_sprite);

    auto start_motion = MoveTo::create(3.0f, Vec2(Director::getInstance()->getWinSize().width / 9.0f, plane_sprite->getPositionY()));
    auto background_motion = MoveBy::create(60.0f, -Vec2(background_sprite->getContentSize().width - Director::getInstance()->getWinSize().width,0.0f));
    

	plane_sprite->runAction(start_motion);
    background_sprite->runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(FirstLevelGameScene::init_listener, this)), background_motion, nullptr));

	this->scheduleUpdate();
    return true;
}

void FirstLevelGameScene::update(float delta)
{
    if (isGameStarted)
    {
        if (isUp)
        {
            plane_sprite->setPosition(plane_sprite->getPositionX(), plane_sprite->getPositionY() + 2.0f);
        }
        else
        {
            plane_sprite->setPosition(plane_sprite->getPositionX(), plane_sprite->getPositionY() - 2.0f);
        }
    }
}

void FirstLevelGameScene::GoToPauseScene(Ref* pSender) {
    auto scene = PauseGameScene::createScene();
    Director::getInstance()->pushScene(scene);
}

void FirstLevelGameScene::onMouseDown(EventMouse* event)
{
    isUp = true;
}

void FirstLevelGameScene::onMouseUp(cocos2d::EventMouse* event)
{
    isUp = false;
}



