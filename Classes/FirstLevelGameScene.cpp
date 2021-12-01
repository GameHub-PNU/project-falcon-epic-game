#include "FirstLevelGameScene.h"
#include "PauseGameScene.h"

USING_NS_CC;

Scene* FirstLevelGameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene -> getPhysicsWorld() -> setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene -> getPhysicsWorld() -> setGravity(Vec2(0, -100));
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
    physics_plane -> setDynamic(true);
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
    physics_plane = PhysicsBody::createBox(Size(plane_sprite -> getContentSize().width,plane_sprite -> getContentSize().height), PhysicsMaterial(45.0f, 0.0f, 0.0f));
    physics_plane -> setDynamic(false);
    physics_plane -> setCollisionBitmask(0x1);
    physics_plane -> setContactTestBitmask(0x1);
    plane_sprite -> setPhysicsBody(physics_plane);
    
    auto wall = Node::create();
    auto wallBody = PhysicsBody::createEdgeBox(Size(2 * Director::getInstance() -> getVisibleSize().width, Director::getInstance() -> getVisibleSize().height) , PhysicsMaterial(0.1f, 1.0f, 0.0f));
    wall->setPhysicsBody(wallBody);
    wall->setPosition(Vec2(Director::getInstance() -> getWinSize().width/2, Director::getInstance() -> getWinSize().height/2));
    addChild(wall);
    
    this->addChild(plane_sprite);

    auto start_motion = MoveTo::create(3.0f, Vec2(Director::getInstance()->getWinSize().width / 9.0f, plane_sprite->getPositionY()));
    auto background_motion = MoveBy::create(60.0f, -Vec2(background_sprite->getContentSize().width - Director::getInstance()->getWinSize().width,0.0f));
    

	plane_sprite->runAction(start_motion);
    background_sprite->runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(FirstLevelGameScene::init_listener, this)), background_motion, nullptr));


    float center = Director::getInstance()->getWinSize().height / 2;
    int height = Director::getInstance()->getWinSize().height;
    for (float x = Director::getInstance()->getWinSize().width; x < (4096 - Director::getInstance() -> getWinSize().width); ) {
        int a =1 + rand() % 5;
        switch (a)
        {
        case 1: 
            startedCoordinates.push_back(Vec2(x, (float)(abs(rand()%(int)(height-center))+center)));
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
        x += 100;
    }
    for (int i = 0; i < startedCoordinates.size(); i++) {
        auto sequenceCloud = Sprite::createWithTexture(cloud->getTexture());
        auto physics_cloud = PhysicsBody::createBox(Size(sequenceCloud -> getContentSize().width,sequenceCloud -> getContentSize().height), PhysicsMaterial(45.0f, 0.0f, 0.0f));
        physics_cloud -> setVelocity(Vec2(-0.1f * Director::getInstance() -> getWinSize().width ,0));
        physics_cloud -> setDynamic(true);
        physics_cloud -> setGravityEnable(false);
        physics_cloud -> setCollisionBitmask(0x2);
        physics_cloud -> setContactTestBitmask(0x2);
        sequenceCloud -> setPhysicsBody(physics_cloud);
        clouds.push_back(sequenceCloud);
        clouds[i]->setPosition(startedCoordinates[i]);
        this->addChild(clouds[i]);
    }


    auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = CC_CALLBACK_1(
                                                        FirstLevelGameScene::onCollision, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


	this->scheduleUpdate();
    return true;
}

void FirstLevelGameScene::update(float delta)
{
    if (background_sprite -> getNumberOfRunningActions() > 0) {
        for (int i = 0; i < clouds.size(); i++) {
            float x = clouds[i]->getPositionX();
            float y = clouds[i]->getPositionY();
            if (x < -40) {
                clouds[i]->setPosition(startedCoordinates[i]);
            }
        }
    } else {
        if (isGameStarted) {
            isGameStarted = false;
            for (int i = 0; i < clouds.size(); i++) {
                clouds[i] -> removeFromParentAndCleanup(true);
            }
            clouds.clear();
            physics_plane -> setDynamic(false);
            physics_plane -> setGravityEnable(false);
            plane_sprite -> runAction(MoveTo::create(3, Vec2(Director::getInstance() -> getWinSize().width, Director::getInstance() -> getWinSize().height/2)));
        }
    }
}

void FirstLevelGameScene::GoToPauseScene(Ref* pSender) {
    auto scene = PauseGameScene::createScene();
    Director::getInstance()->pushScene(scene);
}

void FirstLevelGameScene::onMouseDown(EventMouse* event)
{
    physics_plane -> setDynamic(false);
    Director::getInstance() -> getRunningScene() -> getPhysicsWorld() -> setGravity(Vec2(0, 100));
    physics_plane -> setDynamic(true);
}

void FirstLevelGameScene::onMouseUp(cocos2d::EventMouse* event)
{
    physics_plane -> setDynamic(false);
    Director::getInstance() -> getRunningScene() -> getPhysicsWorld() -> setGravity(Vec2(0, -100));
    physics_plane -> setDynamic(true);
}

bool FirstLevelGameScene::onCollision(PhysicsContact& contact) {
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
     
        
    if (((1 == bodyA->getCollisionBitmask()) && (2 == bodyB->getCollisionBitmask())) || ((2 == bodyA->getCollisionBitmask()) && (1 == bodyB->getCollisionBitmask()))) {
        // Програш
        GoToPauseScene(this);
        return true;
    }

    
    return false;
}




