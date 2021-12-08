#include "GameOverScene.h"
#include "CCVideoManager.h"
#include "AudioEngine.h"
#include "SettingsHandler.h"

USING_NS_CC;

int GameOverScene::current_progress_ = 0;

Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

Scene* GameOverScene::createScene(int progress_percent)
{
    current_progress_ = progress_percent;
    return createScene();
}

void GameOverScene::checkIfLevelCompleted()
{
    if (current_progress_ == 100)
    {
        CCVideoManager::Instance()->PlayVideo("end1.m4v");
    }
    else
    {
        //MessageBox("You lose!", "Defeat");
    }
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    checkIfLevelCompleted();
    experimental::AudioEngine::stop(SettingsHandler::getCurrentAudioId());
    return true;
}



