

#ifndef __THIRD_LEVEL_GAME_SCENE_H__
#define __THIRD_LEVEL_GAME_SCENE_H__

#include "cocos2d.h"

class ThirdLevelGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ThirdLevelGameScene);

    void GoToPauseScene(Ref* pSender);
};

#endif // __THIRD_LEVEL_GAME_SCENE_H__

