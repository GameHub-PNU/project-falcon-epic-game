

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
    cocos2d::Sprite* cloud = cocos2d::Sprite::create("Cloud.png");
    cocos2d::Sprite* background_sprite = cocos2d::Sprite::create("background-first.png");
    cocos2d::PhysicsBody* physics_plane;

    bool isUp = false;
    bool isDown = false;
    bool isGameStarted = false;
    std::vector<cocos2d::Vec2> startedCoordinates;
    std::vector<cocos2d::Sprite*> clouds;
    void GoToPauseScene(Ref* pSender);
    void CallPause();
    void onMouseDown(cocos2d::EventMouse* event);
    void onMouseUp(cocos2d::EventMouse* event);
    bool onCollision(cocos2d::PhysicsContact& contact);

    void init_listener();

    cocos2d::FiniteTimeAction* planeCrush;
};

#endif // __FIRST_LEVEL_GAME_SCENE_H_
