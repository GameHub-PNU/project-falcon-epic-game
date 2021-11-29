#include "SettingsHandler.h"
#include "AudioEngine.h"
#include "cocos2d.h"

float SettingsHandler::soundVolume = 0.1f;
int SettingsHandler::currentAudioId = 0;
float SettingsHandler::getSoundVolume() {
	return soundVolume;
}
void SettingsHandler::setSoundVolume(float volume) {
	soundVolume = volume;
}

int SettingsHandler::getCurrentAudioId()
{
	return currentAudioId;
}

void SettingsHandler::setCurrentAudioId(int t)
{
	currentAudioId = t;
}