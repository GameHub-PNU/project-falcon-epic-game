#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually Bauhaus 93
    CREATE_FUNC(MenuScene);
private:
    cocos2d::Sprite* background_sprite = cocos2d::Sprite::create("menu_background.png");
    cocos2d::Label* gameName = cocos2d::Label::createWithSystemFont("Why I'm not falcon\nwhy I'm not flying", "Arial Black", 60,
        cocos2d::Size::ZERO, cocos2d::TextHAlignment::CENTER);
    int soundId;
	void ExitFromGame();
    void GoToChooseLevelGameScene(Ref* pSender);
    void GoToSettingsScene(Ref* pSender);
};

#endif // __MENU_SCENE_H__