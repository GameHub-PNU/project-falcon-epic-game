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
    physics_plane -> setAngularVelocity(-0.18f);
    physics_plane -> setAngularDamping(0.3f);
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
    auto animation = Animation::create();
    animation->addSpriteFrameWithFile("FirstBackgroundAnimation/PlaneCrush1.png");
    animation->addSpriteFrameWithFile("FirstBackgroundAnimation/PlaneCrush2.png");
    animation->addSpriteFrameWithFile("FirstBackgroundAnimation/PlaneCrush3.png");
    animation->addSpriteFrameWithFile("FirstBackgroundAnimation/PlaneCrush4.png");
    animation->addSpriteFrameWithFile("FirstBackgroundAnimation/PlaneCrush5.png");
    animation->addSpriteFrameWithFile("FirstBackgroundAnimation/PlaneCrush6.png");
    animation->setDelayPerUnit(0.25f);
    animation->setLoops(1);
    planeCrush = Animate::create(animation);

    background_sprite->setPosition(0.0f, Director::getInstance()->getWinSize().height / 2.0f);
    background_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->addChild(background_sprite);
    
    std::vector<Vec2> planePolygon;
    planePolygon.push_back(Vec2(-41, -20));
    planePolygon.push_back(Vec2(-42, 0));
    planePolygon.push_back(Vec2(-48, 0));
    planePolygon.push_back(Vec2(-43, 15));
    planePolygon.push_back(Vec2(-32, 20));
    planePolygon.push_back(Vec2(48, 0));
    planePolygon.push_back(Vec2(17, -14));
    planePolygon.push_back(Vec2(14, -10));
    planePolygon.push_back(Vec2(-17, -20));

    

    plane_sprite->setPosition(-2.0f * plane_sprite->getContentSize().width, Director::getInstance()->getWinSize().height / 2.0f);
    physics_plane = PhysicsBody::createPolygon(planePolygon.data(),planePolygon.size() ,PhysicsMaterial(45.0f, 0.0f, 0.0f));
    physics_plane -> setDynamic(false);
    physics_plane -> setCollisionBitmask(0x1);
    physics_plane -> setContactTestBitmask(0x1);
    physics_plane -> setMass(300.0f);
    plane_sprite -> setPhysicsBody(physics_plane);
    
    auto wall = Node::create();
    auto wallBody = PhysicsBody::createEdgeBox(Size(2 * Director::getInstance() -> getVisibleSize().width, Director::getInstance() -> getVisibleSize().height) , PhysicsMaterial(0.0f, 0.0f, 0.0f));
    wallBody -> setCollisionBitmask(0x3);
    wallBody -> setContactTestBitmask(0x3);
    wall->setPhysicsBody(wallBody);
    wall->setPosition(Vec2(Director::getInstance() -> getWinSize().width/2, Director::getInstance() -> getWinSize().height/2));
    addChild(wall);
    
    this->addChild(plane_sprite);

    auto start_motion = MoveTo::create(3.0f, Vec2(Director::getInstance()->getWinSize().width / 9.0f, plane_sprite->getPositionY()));
    auto background_motion = MoveBy::create(60.0f, -Vec2(background_sprite->getContentSize().width - Director::getInstance()->getWinSize().width,0.0f));
    

	plane_sprite->runAction(start_motion);
    background_sprite->runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(FirstLevelGameScene::init_listener, this)), background_motion, nullptr));


    sixthSizeOfHeight = Director::getInstance()->getWinSize().height / 6;

    cloudPolygon.push_back(Vec2(-72, -20));
    cloudPolygon.push_back(Vec2(-72, -12));
    cloudPolygon.push_back(Vec2(-66, 5));
    cloudPolygon.push_back(Vec2(-49, 21));
    cloudPolygon.push_back(Vec2(-19, 32));
    cloudPolygon.push_back(Vec2(0, 32));
    cloudPolygon.push_back(Vec2(38, 25));
    cloudPolygon.push_back(Vec2(72, -4));
    cloudPolygon.push_back(Vec2(72, -20));
    cloudPolygon.push_back(Vec2(61, -33));
    cloudPolygon.push_back(Vec2(-55, -33));
    cloudPolygon.push_back(Vec2(-66, -30));

    
    
    for (int i = 0; i < Director::getInstance() -> getWinSize().width / cloud -> getContentSize().width; i++) {
        auto cloud1 = createCloud(Vec2(Director::getInstance()->getWinSize().width + i * cloud -> getContentSize().width, (1 + rand() % 5) * sixthSizeOfHeight));
        auto cloud2 = createCloud(Vec2(Director::getInstance()->getWinSize().width + i * cloud -> getContentSize().width, (1 + rand() % 5) * sixthSizeOfHeight));
        clouds.push_back(cloud1);
        clouds.push_back(cloud2);
        this->addChild(cloud1);
        this->addChild(cloud2);
    }


    auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = CC_CALLBACK_1(
                                                        FirstLevelGameScene::onCollision, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    planeCrush->retain();
	this->scheduleUpdate();
    return true;
}

Sprite* FirstLevelGameScene::createCloud(Vec2 coordinates) {
    auto sequenceCloud = Sprite::createWithTexture(cloud->getTexture());
    auto physics_cloud = PhysicsBody::createPolygon(cloudPolygon.data(),cloudPolygon.size() ,PhysicsMaterial(2000.0f, 0.0f, 0.0f));
    physics_cloud -> setVelocity(Vec2(-0.1f * Director::getInstance() -> getWinSize().width ,0));
    physics_cloud -> setDynamic(true);
    
    physics_cloud -> setGravityEnable(false);
    physics_cloud -> setCollisionBitmask(0x2);
    physics_cloud -> setContactTestBitmask(0x2);
    sequenceCloud -> setPhysicsBody(physics_cloud);
    sequenceCloud -> setPosition(coordinates);
                                 
    return sequenceCloud;
}

void FirstLevelGameScene::update(float delta)
{
    if (isGameStarted) {
        if (background_sprite -> getNumberOfRunningActions() > 0) {
            for (int i = 0; i < clouds.size(); i++) {
                if (clouds[i]->getPositionX() < 0 - clouds[i] -> getContentSize().width/2) {
                    clouds[i] -> setPosition(Vec2(Director::getInstance()->getWinSize().width + clouds[i] -> getContentSize().width/2, (1 + rand() % 5) * sixthSizeOfHeight));
                }
            }
        } else {
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

void FirstLevelGameScene::CallPause()
{
    GoToPauseScene(this);
}

void FirstLevelGameScene::onMouseDown(EventMouse* event)
{
    physics_plane -> setDynamic(false);
    Director::getInstance() -> getRunningScene() -> getPhysicsWorld() -> setGravity(Vec2(0, 100));
    physics_plane -> setDynamic(true);
    physics_plane -> setAngularDamping(0.3f);
    physics_plane -> setAngularVelocity(0.18f);
}

void FirstLevelGameScene::onMouseUp(cocos2d::EventMouse* event)
{
    physics_plane -> setDynamic(false);
    Director::getInstance() -> getRunningScene() -> getPhysicsWorld() -> setGravity(Vec2(0, -100));
    physics_plane -> setDynamic(true);
    physics_plane -> setAngularDamping(0.3f);
    physics_plane -> setAngularVelocity(-0.18f);
}

bool FirstLevelGameScene::onCollision(PhysicsContact& contact) {
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
        
    if (((1 == bodyA->getCollisionBitmask()) && (2 == bodyB->getCollisionBitmask())) || ((2 == bodyA->getCollisionBitmask()) && (1 == bodyB->getCollisionBitmask()))) {
        // Програш
        
        plane_sprite->runAction(Sequence::create(planeCrush, CallFuncN::create(CC_CALLBACK_1(FirstLevelGameScene::GoToPauseScene, this)), nullptr));
        return false;
    } else if (((1 == bodyA->getCollisionBitmask()) && (3 == bodyB->getCollisionBitmask())) || ((3 == bodyA->getCollisionBitmask()) && (1 == bodyB->getCollisionBitmask()))) {
        physics_plane -> setAngularVelocity(0);
        return true;
    }
    
    return false;
}




