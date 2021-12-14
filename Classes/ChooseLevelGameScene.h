#ifndef __CHOOSE_LEVEL_GAME_SCENE__
#define __CHOOSE_LEVEL_GAME_SCENE__

#include <vector>
#include "cocos2d.h"
#include "ui/UISlider.h"

class ChooseLevelGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ChooseLevelGameScene);
private:
    cocos2d::Sprite* background_sprite_ = cocos2d::Sprite::create("choose-level-background.png");

    std::vector<cocos2d::ui::Slider*> level_progresses_;
    std::vector<cocos2d::Label*> percentages_ = { cocos2d::Label::createWithSystemFont("0%", "Arial", 19),
    	cocos2d::Label::createWithSystemFont("0%", "Arial", 19), cocos2d::Label::createWithSystemFont("0%", "Arial", 19) };
    
    void getUserRecords();

    void goToFirstLevelGameScene(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void goToSecondLevelGameScene(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void goToThirdLevelGameScene(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void goToMenuScene(Ref* pSender);
};

#endif // __MENU_SCENE_H__
