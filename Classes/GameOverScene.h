#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    static cocos2d::Scene* createScene(int progress_percent, int levelStatus);
    ~GameOverScene() override;
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);

    void restartGame(Ref* pSender);
    void goToMenuScene(Ref* pSender);
    void goToNextLevel(Ref* pSender);

private:
    cocos2d::Sprite* background_sprite_ = cocos2d::Sprite::create("GameOverBackground.png");
    cocos2d::Label* round_status_ = cocos2d::Label::createWithSystemFont("Status", "Arial Black", 60,
        cocos2d::Size::ZERO, cocos2d::TextHAlignment::CENTER);

    inline static int current_progress_ = 0;
    inline static int level_status_ = 0;
    void checkIfLevelCompleted();

};

#endif // __MENU_SCENE_H__

