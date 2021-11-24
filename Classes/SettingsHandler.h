
//#include<cocos2d.h>
//#include "SimpleAudioEngine.h"
//using namespace CocosDenshion;

class SettingsHandler
{
public:
	static float getSoundVolume();

	static void setSoundVolume(float volume);

	static int getCurrentAudioId();
	static void setCurrentAudioId(int t);
private:
	static float soundVolume;
	static int currentAudioId;

};

