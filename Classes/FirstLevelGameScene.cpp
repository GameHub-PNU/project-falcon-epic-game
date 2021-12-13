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
	plane_crush_ = Animate::create(animation);
	plane_crush_->retain();
}

void FirstLevelGameScene::initPlanePhysicsBody()
{
	std::vector<Vec2> planePolygon = { Vec2(-41, -20), Vec2(-42, 0), Vec2(-48, 0), Vec2(-43, 15),
		Vec2(-32, 20), Vec2(48, 0), Vec2(17, -14), Vec2(14, -10), Vec2(-17, -20) };

	physics_plane_ = PhysicsBody::createPolygon(planePolygon.data(), planePolygon.size(), PhysicsMaterial(45.0f, 0.0f, 0.0f));
	physics_plane_->setDynamic(false);
	physics_plane_->setCollisionBitmask(0x1);
	physics_plane_->setContactTestBitmask(0x1);
	physics_plane_->setMass(300.0f);
	plane_sprite_->setPhysicsBody(physics_plane_);
}

void FirstLevelGameScene::addBackground()
{
	background_sprite_->setPosition(0.0f, Director::getInstance()->getWinSize().height / 2.0f);
	background_sprite_->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->addChild(background_sprite_, 1);
}

void FirstLevelGameScene::initListener()
{
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(FirstLevelGameScene::onMouseDown, this);
	listener->onMouseUp = CC_CALLBACK_1(FirstLevelGameScene::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	physics_plane_->setDynamic(true);
	physics_plane_->setAngularVelocity(-angular_velocity_plane_coeff_);
	physics_plane_->setAngularDamping(angular_damping_plane_coeff_);
	is_game_started_ = true;
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
	plane_sprite_->setPosition(-2.0f * plane_sprite_->getContentSize().width, Director::getInstance()->getWinSize().height / 2.0f);
	this->addChild(plane_sprite_, 3);

	auto start_motion = MoveTo::create(3.0f, Vec2(Director::getInstance()->getWinSize().width / 9.0f, plane_sprite_->getPositionY()));
	auto background_motion = MoveBy::create(background_movement_time_, -Vec2(background_sprite_->getContentSize().width - Director::getInstance()->getWinSize().width, 0.0f));

	plane_sprite_->runAction(start_motion);
	background_sprite_->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(FirstLevelGameScene::turnOnMusic, this)),
		DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(FirstLevelGameScene::initListener, this)), background_motion, nullptr));
}

void FirstLevelGameScene::initClouds()
{
	cloud_polygons_.reserve(5);
	std::vector<Vec2> first_cloud = { Vec2(-74, 8), Vec2(-54, 18), Vec2(-13, 21), Vec2(3, 36), Vec2(18, 32), Vec2(45, 16), Vec2(49, -6),
		Vec2(74, -17), Vec2(74, -25),  Vec2(11, -18), Vec2(-3, -13), Vec2(-27, -33), Vec2(-34, -27), Vec2(-44, -33), Vec2(-62, -31),
		Vec2(-58, -7), Vec2(-50, -3), Vec2(-66, -2) };

	std::vector<Vec2> second_cloud = { Vec2(-72, -7), Vec2(-62, -9), Vec2(-49, 17), Vec2(-37, 20), Vec2(-32, 27), Vec2(-23, 25), Vec2(-16, 3),
		Vec2(-7, 0), Vec2(10, 27),  Vec2(28, 28), Vec2(12, 5), Vec2(34, 1), Vec2(43, 9), Vec2(60, 6), Vec2(64, -3),
		Vec2(45, -15), Vec2(-53, -21), Vec2(-72, -13) };

	std::vector<Vec2> third_cloud = { Vec2(-52, -6), Vec2(-24, 10), Vec2(2, 19), Vec2(22, 37), Vec2(38, 26), Vec2(51, 13), Vec2(37, -8),
		Vec2(41, -25), Vec2(0, -17),  Vec2(-44, -21), Vec2(-54, -18) };

	std::vector<Vec2> fourth_cloud = { Vec2(-51, 4), Vec2(-44, 30), Vec2(1, 43), Vec2(11, 20), Vec2(59, -1), Vec2(19, -11), Vec2(31, -34),
		Vec2(7, -37), Vec2(-3, -27),  Vec2(-30, -20), Vec2(-46, -9), Vec2(-61, -12) };

	std::vector<Vec2> fifth_cloud = { Vec2(-67, -5), Vec2(-37, -11), Vec2(-12, 16), Vec2(10, 19), Vec2(45, 12), Vec2(66, -5), Vec2(66, -14),
		Vec2(6, -13), Vec2(-53, -17),  Vec2(-68, -14) };

	cloud_polygons_.push_back(first_cloud);
	cloud_polygons_.push_back(second_cloud);
	cloud_polygons_.push_back(third_cloud);
	cloud_polygons_.push_back(fourth_cloud);
	cloud_polygons_.push_back(fifth_cloud);

	const int offset = 30;
	for (int i = 0; i < Director::getInstance()->getWinSize().width / (clouds_sprites_[0]->getContentSize().width + offset); i++) {
		for (int j = 0; j < clouds_in_column_; ++j)
		{
			auto next_cloud = createCloud(Vec2(Director::getInstance()->getWinSize().width + i * (clouds_sprites_[0]->getContentSize().width + offset),
				rand() % (lines_quantity_ + 1) * eighth_size_of_height_));
			clouds_.push_back(next_cloud);
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
	level_progress_bar_->setEnabled(false);
	this->addChild(level_progress_bar_, 5);
}

void FirstLevelGameScene::updateProgressBar(float dt)
{
	level_progress_bar_->setPercent(++current_percent_);
}

void FirstLevelGameScene::turnOnMusic()
{
     sound_id_ = experimental::AudioEngine::play2d("backgroundSongLevel1.mp3", true, SettingsHandler::getSoundVolume());
	 SettingsHandler::setCurrentAudioId(sound_id_);
}

Sprite* FirstLevelGameScene::createCloud(Vec2 coordinates)
{
	int cloud_number = rand() % clouds_sprites_.size();
	auto sequenceCloud = Sprite::createWithTexture(clouds_sprites_[cloud_number]->getTexture());
	auto physics_cloud = PhysicsBody::createPolygon(cloud_polygons_[cloud_number].data(), cloud_polygons_[cloud_number].size(),
		PhysicsMaterial(2000.0f, 0.0f, 0.0f));
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
	experimental::AudioEngine::pauseAll();
	auto scene = PauseGameScene::createScene(1);
	Director::getInstance()->pushScene(scene);
}

void FirstLevelGameScene::goToGameOverScene(Ref* pSender)
{
	auto scene = GameOverScene::createScene(current_percent_, 1);
	Director::getInstance()->replaceScene(scene);
}

void FirstLevelGameScene::onMouseDown(EventMouse* event)
{
	physics_plane_->setDynamic(false);
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setGravity(Vec2(0, 100));
	physics_plane_->setDynamic(true);
	//physics_plane_ -> setAngularVelocity(angular_velocity_plane_coeff_);
	//physics_plane_ -> setAngularDamping(0.15f);
	if (plane_sprite_->getRotation() > -10) {
		physics_plane_->setAngularDamping((angular_velocity_plane_coeff_ - physics_plane_->getAngularVelocity()) * 0.4166f);
		physics_plane_->setAngularVelocity(angular_velocity_plane_coeff_ - physics_plane_->getAngularVelocity());
	}

}

void FirstLevelGameScene::onMouseUp(EventMouse* event)
{
	physics_plane_->setDynamic(false);
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setGravity(Vec2(0, -100));
	physics_plane_->setDynamic(true);
	//physics_plane_->setAngularVelocity(-angular_velocity_plane_coeff_ - physics_plane_->getAngularVelocity());
	//physics_plane_->setAngularDamping(physics_plane_->getAngularVelocity() * angular_damping_plane_coeff_ / angular_velocity_plane_coeff_);
	if (plane_sprite_->getRotation() < 10) {
		physics_plane_->setAngularDamping(std::abs((-angular_velocity_plane_coeff_ - physics_plane_->getAngularVelocity()) * 0.4166f));
		physics_plane_->setAngularVelocity(-angular_velocity_plane_coeff_ - physics_plane_->getAngularVelocity());
	}

}

bool FirstLevelGameScene::onCollision(PhysicsContact& contact)
{
	PhysicsBody* bodyA = contact.getShapeA()->getBody();
	PhysicsBody* bodyB = contact.getShapeB()->getBody();

	if (((1 == bodyA->getCollisionBitmask()) && (2 == bodyB->getCollisionBitmask())) || ((2 == bodyA->getCollisionBitmask()) && (1 == bodyB->getCollisionBitmask())))
	{
		if (is_game_started_)
		{
			plane_sprite_->runAction(Sequence::create(plane_crush_, CallFuncN::create(CC_CALLBACK_1(FirstLevelGameScene::goToGameOverScene, this)), nullptr));
			is_game_started_ = false;
		}
		return false;
	}
	if (((1 == bodyA->getCollisionBitmask()) && (3 == bodyB->getCollisionBitmask())) || ((3 == bodyA->getCollisionBitmask()) && (1 == bodyB->getCollisionBitmask())))
	{
		physics_plane_->setAngularVelocity(0);
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

	auto pauseMenuItem = MenuItemImage::create("PauseButton.png", "PauseButton.png", CC_CALLBACK_1(FirstLevelGameScene::goToPauseScene, this));
	pauseMenuItem->setScale(0.4f);
	auto onGameItem = Menu::create(pauseMenuItem, NULL);
	onGameItem->setPosition(Vec2(Director::getInstance()->getWinSize().width -(pauseMenuItem->getContentSize().width*0.3), Director::getInstance()->getWinSize().height - pauseMenuItem->getContentSize().height * 0.3));
	this->addChild(onGameItem, 6);

	this->scheduleUpdate();
	this->schedule(schedule_selector(FirstLevelGameScene::updateProgressBar), level_time_duration_in_seconds_ / 100.0f);
	return true;
}

void FirstLevelGameScene::update(float delta)
{
	if (is_game_started_)
	{
		if (background_sprite_->getNumberOfRunningActions() > 0)
		{
			for (const auto& cloud_to_move : clouds_)
			{
				if (cloud_to_move->getPositionX() < 0 - cloud_to_move->getContentSize().width / 2)
				{
					cloud_to_move->setPosition(Vec2(Director::getInstance()->getWinSize().width + cloud_to_move->getContentSize().width / 2.0f,
						rand() % (lines_quantity_ + 1) * eighth_size_of_height_));
				}
			}
		}
		else
		{
			is_game_started_ = false;
			for (const auto& cloud_to_remove : clouds_)
			{
				cloud_to_remove->removeFromParentAndCleanup(true);
			}
			clouds_.clear();
			physics_plane_->setDynamic(false);
			physics_plane_->setGravityEnable(false);
			_eventDispatcher->removeAllEventListeners();
			plane_sprite_->runAction(Sequence::create(MoveTo::create(3, Vec2(Director::getInstance()->getWinSize().width,
				Director::getInstance()->getWinSize().height / 2.0f)), CallFuncN::create(CC_CALLBACK_1(FirstLevelGameScene::goToGameOverScene, this)), nullptr));
		}
	}
}
