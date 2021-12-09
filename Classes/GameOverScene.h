#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    static cocos2d::Scene* createScene(int progress_percent, int levelStatus);

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);

    void RestartGame(Ref* pSender);
    void GoToMenuScene(Ref* pSender);

private:
    cocos2d::Sprite* background_sprite = cocos2d::Sprite::create("GameOverBackground.png");
    cocos2d::Label* roundStatus = cocos2d::Label::createWithSystemFont("Status", "Arial Black", 60,
        cocos2d::Size::ZERO, cocos2d::TextHAlignment::CENTER);

    static int current_progress_;
    static int level_status_;
    void checkIfLevelCompleted();

};

#endif // __MENU_SCENE_H__

