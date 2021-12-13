#ifndef __SECOND_LEVEL_GAME_SCENE_H__
#define __SECOND_LEVEL_GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/UISlider.h"

class SecondLevelGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;

    // implement the "static create()" method manually
    CREATE_FUNC(SecondLevelGameScene);
    void update(float delta) override;

private:
    cocos2d::Sprite* plane_sprite_ = cocos2d::Sprite::create("plane.png");
    std::vector<cocos2d::Sprite*> clouds_sprites_ = { cocos2d::Sprite::create("SecondLevelClouds/FirstCloud.png"), cocos2d::Sprite::create("SecondLevelClouds/SecondCloud.png"),
        cocos2d::Sprite::create("SecondLevelClouds/ThirdCloud.png"), cocos2d::Sprite::create("SecondLevelClouds/FourthCloud.png"),
        cocos2d::Sprite::create("SecondLevelClouds/FifthCloud.png") };
    cocos2d::Sprite* background_sprite_ = cocos2d::Sprite::create("SecondBackground.png");
    cocos2d::PhysicsBody* physics_plane_ = nullptr;
    cocos2d::ui::Slider* level_progress_bar_ = cocos2d::ui::Slider::create();
    int current_percent_ = level_progress_bar_->getPercent();
    std::vector<std::vector<cocos2d::Vec2>> cloud_polygons_;

    int sound_id_;
    bool is_game_started_ = false;
    int clouds_in_column_ = 3;
    const int lines_quantity_ = 8;
    const float angular_velocity_plane_coeff_ = 0.18f;
    const float angular_damping_plane_coeff_ = 0.3f;
    const float level_time_duration_in_seconds_ = 96.0f;
    const float background_movement_time_ = 90.0f;

    float eighth_size_of_height_ = cocos2d::Director::getInstance()->getWinSize().height / lines_quantity_;

    std::vector<cocos2d::Sprite*> clouds_;
    cocos2d::FiniteTimeAction* plane_crush_ = nullptr;

    void addPlaneAnimation();

    void initPlanePhysicsBody();

    void addBackground();

    void initListener();

    void initGameBound();

    void initPlaneAndBackgroundPosition();

    void initClouds();

    void addPlaneAndCloudsCollision();

    void initLevelProgressBar();

    void updateProgressBar(float dt);

    void turnOnMusic();

    void goToPauseScene(Ref* pSender);

    void goToGameOverScene(Ref* pSender);

    void onMouseDown(cocos2d::EventMouse* event);

    void onMouseUp(cocos2d::EventMouse* event);

    bool onCollision(cocos2d::PhysicsContact& contact);

    cocos2d::Sprite* createCloud(cocos2d::Vec2 coordinates);
};

#endif // __SECOND_LEVEL_GAME_SCENE_H__