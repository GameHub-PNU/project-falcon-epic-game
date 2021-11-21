#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"

class SettingsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(SettingsScene);
    void GoToMenuScene(Ref* pSender);

};

#endif // __THIRD_LEVEL_GAME_SCENE_H__
