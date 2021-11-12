
#ifndef __PAUSE_GAME_SCENE_H__
#define __PAUSE_GAME_SCENE_H__

#include "cocos2d.h"

class PauseGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(PauseGameScene);

    void ResumeGame(Ref* pSender);
};

#endif //__PAUSE_GAME_SCENE_H__