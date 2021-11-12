

#ifndef __FIRST_LEVEL_GAME_SCENE_H__
#define __FIRST_LEVEL_GAME_SCENE_H__

#include "cocos2d.h"

class FirstLevelGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(FirstLevelGameScene);

    void GoToPauseScene(Ref* pSender);
};

#endif // __FIRST_LEVEL_GAME_SCENE_H_
