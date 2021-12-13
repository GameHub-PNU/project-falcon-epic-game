
#ifndef __PAUSE_GAME_SCENE_H__
#define __PAUSE_GAME_SCENE_H__

#include "cocos2d.h"

class PauseGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    static cocos2d::Scene* createScene(int levelStatus);

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(PauseGameScene);

    void resumeGame(Ref* pSender);
    void restartGame(Ref* pSender);
    void goToMenuScene(Ref* pSender);

private:
    cocos2d::Sprite* background_sprite_ = cocos2d::Sprite::create("PauseBackground.png");
    inline static int level_status_ = 0;
};

#endif //__PAUSE_GAME_SCENE_H__