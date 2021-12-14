#include "GameOverScene.h"
#include "CCVideoManager.h"
#include "AudioEngine.h"
#include "SettingsHandler.h"

#include "FirstLevelGameScene.h"
#include "SecondLevelGameScene.h"
#include "ThirdLevelGameScene.h"

#include "MenuScene.h"
#include <fstream>
USING_NS_CC;

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

Scene* GameOverScene::createScene(int progress_percent, int levelStatus)
{
	current_progress_ = progress_percent;
	level_status_ = levelStatus;
	return createScene();
}

GameOverScene::~GameOverScene()
{
	if (current_progress_ == 100)
	{
		CCVideoManager::Instance()->DestroyInstance();
	}
}

void GameOverScene::checkIfLevelCompleted()
{
	if (current_progress_ == 100)
	{
		round_status_->setString("You win!");
		CCVideoManager::Instance()->PlayVideo("end1.m4v");
		experimental::AudioEngine::play2d("EndLevelSound.mp3", false, SettingsHandler::getSoundVolume());
	}
	else
	{
		round_status_->setString("You lose!");
		experimental::AudioEngine::play2d("YouLoseSong.mp3", true, SettingsHandler::getSoundVolume());
	}

	if (SettingsHandler::getMaxProgress().at(level_status_ - 1) < current_progress_)
	{
		SettingsHandler::getMaxProgress().at(level_status_ - 1) = current_progress_;
		std::ofstream update_records("Backup/records.txt");
		
		for (const int i : SettingsHandler::getMaxProgress())
		{
			update_records << i << '\n';
		}
		update_records.close();
	}
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
	checkIfLevelCompleted();

	background_sprite_->setPosition(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 2.0f);
	this->addChild(background_sprite_);

	auto restartMenuItem = MenuItemImage::create("RESTART.png", "RESTART.png", CC_CALLBACK_1(GameOverScene::restartGame, this));
	restartMenuItem->setScale(0.6f);
	auto exitMenuItem = MenuItemImage::create("MENU.png", "MENU.png", CC_CALLBACK_1(GameOverScene::goToMenuScene, this));
	exitMenuItem->setScale(0.6f);
	auto nextLevelItem = MenuItemImage::create("NEXTLEVEL.png", "NEXTLEVEL.png", CC_CALLBACK_1(GameOverScene::goToNextLevel, this));
	nextLevelItem->setScale(0.6f);

	Menu* MenuItems;

	if (current_progress_ == 100)
	{
		auto right_confetti = ParticleFireworks::create();
		right_confetti->retain();
		right_confetti->setRotation(45);
		background_sprite_->addChild(right_confetti);
		const char s_stars1[] = "stars.png";
		right_confetti->setTexture(Director::getInstance()->getTextureCache()->addImage(s_stars1));
		right_confetti->setScale(1.5f);
		right_confetti->setPosition(0.0f, 0.0f);
		auto left_confetti = ParticleFireworks::create();
		left_confetti->retain();
		background_sprite_->addChild(left_confetti);
		left_confetti->setRotation(-45);
		left_confetti->setScale(1.5f);
		left_confetti->setTexture(Director::getInstance()->getTextureCache()->addImage(s_stars1));
		left_confetti->setPosition(Director::getInstance()->getWinSize().width, 0.0f);
		if (level_status_ != 3)
		{
			MenuItems = Menu::create(nextLevelItem, restartMenuItem, exitMenuItem, NULL);
		}
		else 
		{
			MenuItems = Menu::create(restartMenuItem, exitMenuItem, NULL);
		}
	}
	else 
	{
		MenuItems = Menu::create(restartMenuItem, exitMenuItem, NULL);
		Label* score_result = Label::createWithSystemFont(StringUtils::format("Your progress: %d%%", current_progress_), "Arial Black", 40);
		score_result->setPosition(Director::getInstance()->getWinSize().width / 2.0f, 1.55f * MenuItems->getPosition().y);
		score_result->enableShadow(Color4B::BLACK, Size(5, -5), 2);
		this->addChild(score_result);
	}
	MenuItems->alignItemsVerticallyWithPadding(35);
	this->addChild(MenuItems);
	round_status_->setPosition(Director::getInstance()->getWinSize().width / 2.0f, 1.75f * MenuItems->getPosition().y);
	round_status_->enableShadow(Color4B::BLACK, Size(5, -5), 2);
	this->addChild(round_status_);

	return true;
}

void GameOverScene::restartGame(Ref* pSender)
{
	experimental::AudioEngine::stopAll();
	Scene* scene = nullptr;
	switch (level_status_)
	{
		case 1: scene = FirstLevelGameScene::createScene(); break;
		case 2: scene = SecondLevelGameScene::createScene(); break;
		case 3: scene = ThirdLevelGameScene::createScene(); break;
		default: break;
	}
	Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene));
}

void GameOverScene::goToMenuScene(Ref* pSender)
{
	experimental::AudioEngine::stopAll();
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}

void GameOverScene::goToNextLevel(Ref* pSender)
{
	Scene* scene = nullptr;
	switch (level_status_)
	{
		case 1: scene = SecondLevelGameScene::createScene(); break;
		case 2: scene = ThirdLevelGameScene::createScene(); break;
		default: break;
	}
	Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene));
}
