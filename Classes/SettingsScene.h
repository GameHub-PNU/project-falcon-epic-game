#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"
#include <ui/CocosGUI.h>

class SettingsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
   
    // implement the "static create()" method manually
    CREATE_FUNC(SettingsScene);
private:

    cocos2d::Label* volume_name_ = cocos2d::Label::createWithSystemFont("VOLUME", "Arial Black", 60,
        cocos2d::Size::ZERO, cocos2d::TextHAlignment::CENTER);

    void goToMenuScene(Ref* pSender);
    void changeVolume(Ref* pSender, cocos2d::ui::Slider::EventType type);
};

#endif // __THIRD_LEVEL_GAME_SCENE_H__
