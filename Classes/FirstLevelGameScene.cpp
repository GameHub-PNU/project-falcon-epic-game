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
    srand(time(NULL));
    background_sprite->setPosition(0.0f, Director::getInstance()->getWinSize().height / 2.0f);
    background_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->addChild(background_sprite);
    plane_sprite->setPosition(-2.0f * plane_sprite->getContentSize().width, Director::getInstance()->getWinSize().height / 2.0f);
    this->addChild(plane_sprite);

    auto start_motion = MoveTo::create(3.0f, Vec2(Director::getInstance()->getWinSize().width / 9.0f, plane_sprite->getPositionY()));
    auto background_motion = MoveBy::create(60.0f, -Vec2(background_sprite->getContentSize().width - Director::getInstance()->getWinSize().width,0.0f));
    

	plane_sprite->runAction(start_motion);
    background_sprite->runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(FirstLevelGameScene::init_listener, this)), background_motion, nullptr));


    float center = Director::getInstance()->getWinSize().height / 2;
    int height = Director::getInstance()->getWinSize().height;
    for (float x = Director::getInstance()->getWinSize().width; x < 4096; ) {
        int a =1 + rand() % 5;
        switch (a)
        {
        case 1: 
            startedCoordinates.push_back(Vec2(x,  (float)(abs(rand()%(int)(height-center))+center)));
            break;

        case 2:
            startedCoordinates.push_back(Vec2(x, 45 + rand() % (int)center));
            break;
        case 3:
            startedCoordinates.push_back(Vec2(x, center));
            break;
        case 4:
            startedCoordinates.push_back(Vec2(x, (float)(abs(rand() % (int)(height - center)) + center)));
            startedCoordinates.push_back(Vec2(x, center));
            break;
        case 5:
            startedCoordinates.push_back(Vec2(x, center));
            startedCoordinates.push_back(Vec2(x, 45 + rand() % (int)center));
        case 6:
            startedCoordinates.push_back(Vec2(x, (float)(abs(rand() % (int)(height - center)) + center)));
            startedCoordinates.push_back(Vec2(x, 45 + rand() % (int)center));
            break;
        default:
            break;
        }
        x += 250;
    }
    for (int i = 0; i < startedCoordinates.size(); i++) {
        auto cloud = Sprite::create("Cloud.png");
        clouds.push_back(cloud);
        clouds[i]->setPosition(startedCoordinates[i]);
        this->addChild(clouds[i]);
    }




	this->scheduleUpdate();
    return true;
}

void FirstLevelGameScene::update(float delta)
{
    if (isGameStarted)
    {
        if (isUp)
        {
           if(plane_sprite->getPositionY()+plane_sprite->getContentSize().height/2<Director::getInstance()->getWinSize().height)
            plane_sprite->setPosition(plane_sprite->getPositionX(), plane_sprite->getPositionY() + 2.0f);
        }
        else
        {
            if (plane_sprite->getPositionY() - plane_sprite->getContentSize().height / 2 >0)
            plane_sprite->setPosition(plane_sprite->getPositionX(), plane_sprite->getPositionY() - 2.0f);
        }
    }
    for (int i = 0; i < clouds.size(); i++) {
        clouds[i]->setPosition(Vec2(clouds[i]->getPositionX() - 1, clouds[i]->getPositionY()));
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



