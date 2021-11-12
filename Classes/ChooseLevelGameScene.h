

#ifndef __CHOOSE_LEVEL_GAME_SCENE__
#define __CHOOSE_LEVEL_GAME_SCENE__

#include "cocos2d.h"

class ChooseLevelGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ChooseLevelGameScene);
    void GoToFirstLevelGameScene(Ref* pSender);
    void GoToSecondLevelGameScene(Ref* pSender);
    void GoToThirdLevelGameScene(Ref* pSender);
};

#endif // __MENU_SCENE_H__