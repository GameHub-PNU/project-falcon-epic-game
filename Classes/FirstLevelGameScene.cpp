#include "FirstLevelGameScene.h"

#include "AudioEngine.h"
#include "PauseGameScene.h"
#include "GameOverScene.h"
#include "SettingsHandler.h"

USING_NS_CC;

Scene* FirstLevelGameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene -> getPhysicsWorld() -> setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -100));
	auto layer = FirstLevelGameScene::create();
	scene->addChild(layer);
	return scene;
}

void FirstLevelGameScene::addPlaneAnimation()
{
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
	planeCrush->retain();
}

void FirstLevelGameScene::initPlanePhysicsBody()
{
	std::vector<Vec2> planePolygon = { Vec2(-41, -20), Vec2(-42, 0), Vec2(-48, 0), Vec2(-43, 15),
		Vec2(-32, 20), Vec2(48, 0), Vec2(17, -14), Vec2(14, -10), Vec2(-17, -20) };

	physics_plane = PhysicsBody::createPolygon(planePolygon.data(), planePolygon.size(), PhysicsMaterial(45.0f, 0.0f, 0.0f));
	physics_plane->setDynamic(false);
	physics_plane->setCollisionBitmask(0x1);
	physics_plane->setContactTestBitmask(0x1);
	physics_plane->setMass(300.0f);
	plane_sprite->setPhysicsBody(physics_plane);
}

void FirstLevelGameScene::addBackground()
{
	background_sprite->setPosition(0.0f, Director::getInstance()->getWinSize().height / 2.0f);
	background_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->addChild(background_sprite, 1);
}

void FirstLevelGameScene::initListener()
{
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(FirstLevelGameScene::onMouseDown, this);
	listener->onMouseUp = CC_CALLBACK_1(FirstLevelGameScene::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	physics_plane->setDynamic(true);
	physics_plane->setAngularVelocity(-angular_velocity_plane_coeff_);
	physics_plane->setAngularDamping(angular_damping_plane_coeff_);
	turnOnMusic();
	isGameStarted = true;
}

void FirstLevelGameScene::initGameBound()
{
	auto wall = Node::create();
	auto wallBody = PhysicsBody::createEdgeBox(Size(2 * Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	wallBody->setCollisionBitmask(0x3);
	wallBody->setContactTestBitmask(0x3);
	wall->setPhysicsBody(wallBody);
	wall->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 2.0f));
	this->addChild(wall, 2);
}

void FirstLevelGameScene::initPlaneAndBackgroundPosition()
{
	plane_sprite->setPosition(-2.0f * plane_sprite->getContentSize().width, Director::getInstance()->getWinSize().height / 2.0f);
	this->addChild(plane_sprite, 3);

	auto start_motion = MoveTo::create(3.0f, Vec2(Director::getInstance()->getWinSize().width / 9.0f, plane_sprite->getPositionY()));
	auto background_motion = MoveBy::create(60.0f, -Vec2(background_sprite->getContentSize().width - Director::getInstance()->getWinSize().width, 0.0f));

	plane_sprite->runAction(start_motion);
	background_sprite->runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(FirstLevelGameScene::initListener, this)), background_motion, nullptr));
}

void FirstLevelGameScene::initClouds()
{
	cloudPolygon = { Vec2(-72, -20), Vec2(-72, -12), Vec2(-66, 5), Vec2(-49, 21), Vec2(-19, 32), Vec2(0, 32), Vec2(38, 25), Vec2(72, -4),
	Vec2(72, -20), Vec2(61, -33), Vec2(-55, -33), Vec2(-66, -30) };

	const int offset = 30;
	for (int i = 0; i < Director::getInstance()->getWinSize().width / (cloud_sprite_->getContentSize().width + offset); i++) {
		for (int j = 0; j < 2; ++j)
		{
			auto next_cloud = createCloud(Vec2(Director::getInstance()->getWinSize().width + i * (cloud_sprite_->getContentSize().width + offset),
				rand() % (lines_quantity_ + 1) * eighthSizeOfHeight));
			clouds.push_back(next_cloud);
			this->addChild(next_cloud, 4);
		}
	}
}

void FirstLevelGameScene::addPlaneAndCloudsCollision()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(FirstLevelGameScene::onCollision, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void FirstLevelGameScene::initLevelProgressBar()
{
	level_progress_bar_->loadBarTexture("slider_back.png");
	level_progress_bar_->loadProgressBarTexture("slider_filled.png");
	level_progress_bar_->loadSlidBallTextureDisabled("plane.png");
	level_progress_bar_->getSlidBallDisabledRenderer()->setScale(0.6f);
	level_progress_bar_->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 0.95f * Director::getInstance()->getWinSize().height));
	level_progress_bar_->setMaxPercent(3600);
	level_progress_bar_->setEnabled(false);
	this->addChild(level_progress_bar_, 5);
}

void FirstLevelGameScene::turnOnMusic()
{
	int soundId = experimental::AudioEngine::play2d("backgroundSongLevel1.mp3", true, SettingsHandler::getSoundVolume());
	SettingsHandler::setCurrentAudioId(soundId);
}

Sprite* FirstLevelGameScene::createCloud(Vec2 coordinates)
{
	auto sequenceCloud = Sprite::createWithTexture(cloud_sprite_->getTexture());
	auto physics_cloud = PhysicsBody::createPolygon(cloudPolygon.data(), cloudPolygon.size(), PhysicsMaterial(2000.0f, 0.0f, 0.0f));
	physics_cloud->setVelocity(Vec2(-0.1f * Director::getInstance()->getWinSize().width, 0));
	physics_cloud->setDynamic(true);

	physics_cloud->setGravityEnable(false);
	physics_cloud->setCollisionBitmask(0x2);
	physics_cloud->setContactTestBitmask(0x2);
	sequenceCloud->setPhysicsBody(physics_cloud);
	sequenceCloud->setPosition(coordinates);

	return sequenceCloud;
}

void FirstLevelGameScene::goToPauseScene(Ref* pSender)
{
	auto scene = PauseGameScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void FirstLevelGameScene::goToGameOverScene(Ref* pSender)
{
	auto scene = GameOverScene::createScene(current_percent_ / 36);
	Director::getInstance()->replaceScene(scene);
}

void FirstLevelGameScene::onMouseDown(EventMouse* event)
{
	physics_plane->setDynamic(false);
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setGravity(Vec2(0, 100));
	physics_plane->setDynamic(true);
	//physics_plane -> setAngularVelocity(angular_velocity_plane_coeff_);
	//physics_plane -> setAngularDamping(0.15f);
	if (plane_sprite->getRotation() > -10) {
		physics_plane->setAngularDamping((angular_velocity_plane_coeff_ - physics_plane->getAngularVelocity()) * 0.4166f);
		physics_plane->setAngularVelocity(angular_velocity_plane_coeff_ - physics_plane->getAngularVelocity());
	}

}

void FirstLevelGameScene::onMouseUp(EventMouse* event)
{
	physics_plane->setDynamic(false);
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setGravity(Vec2(0, -100));
	physics_plane->setDynamic(true);
	//physics_plane->setAngularVelocity(-angular_velocity_plane_coeff_ - physics_plane->getAngularVelocity());
	//physics_plane->setAngularDamping(physics_plane->getAngularVelocity() * angular_damping_plane_coeff_ / angular_velocity_plane_coeff_);
	if (plane_sprite->getRotation() < 10) {
		physics_plane->setAngularDamping(std::abs((-angular_velocity_plane_coeff_ - physics_plane->getAngularVelocity()) * 0.4166f));
		physics_plane->setAngularVelocity(-angular_velocity_plane_coeff_ - physics_plane->getAngularVelocity());
	}

}

bool FirstLevelGameScene::onCollision(PhysicsContact& contact)
{
	PhysicsBody* bodyA = contact.getShapeA()->getBody();
	PhysicsBody* bodyB = contact.getShapeB()->getBody();

	if (((1 == bodyA->getCollisionBitmask()) && (2 == bodyB->getCollisionBitmask())) || ((2 == bodyA->getCollisionBitmask()) && (1 == bodyB->getCollisionBitmask())))
	{
		// Програш
		plane_sprite->runAction(Sequence::create(planeCrush, CallFuncN::create(CC_CALLBACK_1(FirstLevelGameScene::goToGameOverScene, this)), nullptr));
		return false;
	}
	if (((1 == bodyA->getCollisionBitmask()) && (3 == bodyB->getCollisionBitmask())) || ((3 == bodyA->getCollisionBitmask()) && (1 == bodyB->getCollisionBitmask())))
	{
		physics_plane->setAngularVelocity(0);
		return true;
	}

	return false;
}

// on "init" you need to initialize your instance
bool FirstLevelGameScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	//srand(time(NULL));
	addPlaneAnimation();
	initPlanePhysicsBody();

	addBackground();

	initGameBound();

	initPlaneAndBackgroundPosition();

	initClouds();
	addPlaneAndCloudsCollision();
	initLevelProgressBar();

	this->scheduleUpdate();
	return true;
}

void FirstLevelGameScene::update(float delta)
{
	if (isGameStarted)
	{
		if (background_sprite->getNumberOfRunningActions() > 0)
		{
			level_progress_bar_->setPercent(++current_percent_);
			for (const auto& cloud_to_move : clouds)
			{
				if (cloud_to_move->getPositionX() < 0 - cloud_to_move->getContentSize().width / 2)
				{
					cloud_to_move->setPosition(Vec2(Director::getInstance()->getWinSize().width + cloud_to_move->getContentSize().width / 2.0f,
						rand() % (lines_quantity_ + 1) * eighthSizeOfHeight));
				}
			}
		}
		else
		{
			isGameStarted = false;
			for (const auto& cloud_to_remove : clouds)
			{
				cloud_to_remove->removeFromParentAndCleanup(true);
			}
			clouds.clear();
			physics_plane->setDynamic(false);
			physics_plane->setGravityEnable(false);

			plane_sprite->runAction(Sequence::create(MoveTo::create(3, Vec2(Director::getInstance()->getWinSize().width,
				Director::getInstance()->getWinSize().height / 2.0f)), CallFuncN::create(CC_CALLBACK_1(FirstLevelGameScene::goToGameOverScene, this)), nullptr));

		}
	}
}
