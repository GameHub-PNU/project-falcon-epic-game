#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    static cocos2d::Scene* createScene(int progress_percent);

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);

private:
    static int current_progress_;

    void checkIfLevelCompleted();

};

#endif // __MENU_SCENE_H__

