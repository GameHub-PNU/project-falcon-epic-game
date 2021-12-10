
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

    void ResumeGame(Ref* pSender);
    void RestartGame(Ref* pSender);
    void GoToMenuScene(Ref* pSender);

private:
    cocos2d::Sprite* background_sprite = cocos2d::Sprite::create("PauseBackground.png");
    static int _levelStatus;
};

#endif //__PAUSE_GAME_SCENE_H__