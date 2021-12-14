#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "ui/UIButton.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
private:
    cocos2d::Sprite* background_sprite_ = cocos2d::Sprite::create("menu_background.png");
    cocos2d::ui::Button* department_button_ = cocos2d::ui::Button::create("KNIS_Logo.png");
    cocos2d::ui::Button* gameHub_button_ = cocos2d::ui::Button::create("GameHub_Logo.png");

    cocos2d::Label* game_name_ = cocos2d::Label::createWithSystemFont("The Plane:\nWhy I'm not falcon\nwhy I'm not flying", "Arial Black", 60,
        cocos2d::Size::ZERO, cocos2d::TextHAlignment::CENTER);
    int sound_id_;
    cocos2d::Animation* background_animation_ = cocos2d::Animation::create();

    void addBackgroundAnimation();

	void departmentButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type);

    void gameHubButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void exitFromGame();
    void goToChooseLevelGameScene(Ref* pSender);
    void goToSettingsScene(Ref* pSender);
};

#endif // __MENU_SCENE_H__