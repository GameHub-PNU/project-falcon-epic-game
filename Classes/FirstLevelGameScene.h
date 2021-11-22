

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
    void update(float delta) override;

private:
    cocos2d::Sprite* plane_sprite = cocos2d::Sprite::create("plane.png");
    cocos2d::Sprite* background_sprite = cocos2d::Sprite::create("background-first.png");

    bool isUp = false;
    bool isDown = false;
    bool isGameStarted = false;

    void GoToPauseScene(Ref* pSender);
    void onMouseDown(cocos2d::EventMouse* event);
    void onMouseUp(cocos2d::EventMouse* event);

    void init_listener();

};

#endif // __FIRST_LEVEL_GAME_SCENE_H_
