#ifndef __FIRST_LEVEL_GAME_SCENE_H__
#define __FIRST_LEVEL_GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/UISlider.h"

class FirstLevelGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;

    // implement the "static create()" method manually
    CREATE_FUNC(FirstLevelGameScene);
    void update(float delta) override;

private:
    cocos2d::Sprite* plane_sprite = cocos2d::Sprite::create("plane.png");
    std::vector<cocos2d::Sprite*> clouds_sprites_ = { cocos2d::Sprite::create("FirstLevelClouds/FirstCloud.png"), cocos2d::Sprite::create("FirstLevelClouds/SecondCloud.png"),
    	cocos2d::Sprite::create("FirstLevelClouds/ThirdCloud.png"), cocos2d::Sprite::create("FirstLevelClouds/FourthCloud.png"),
    	cocos2d::Sprite::create("FirstLevelClouds/FifthCloud.png") };
    cocos2d::Sprite* background_sprite = cocos2d::Sprite::create("background-first.png");
    cocos2d::PhysicsBody* physics_plane = nullptr;
    cocos2d::ui::Slider* level_progress_bar_ = cocos2d::ui::Slider::create();
    int current_percent_ = level_progress_bar_->getPercent();
    std::vector<std::vector<cocos2d::Vec2>> cloudPolygons;

    int soundId;
    bool isGameStarted = false;
    int currentCloudIndex = 0;
    int clouds_in_column_ = 2;
    const int lines_quantity_ = 8;
    const float angular_velocity_plane_coeff_ = 0.18f;
    const float angular_damping_plane_coeff_ = 0.3f;
    const float level_time_duration_in_seconds_ = 66.0f;
    const float background_movement_time_ = 60.0f;

	float eighthSizeOfHeight = cocos2d::Director::getInstance()->getWinSize().height / lines_quantity_;

    std::vector<cocos2d::Sprite*> clouds;
    cocos2d::FiniteTimeAction* planeCrush;

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

#endif // __FIRST_LEVEL_GAME_SCENE_H_
