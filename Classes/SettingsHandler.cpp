#include "SettingsHandler.h"

float SettingsHandler::getSoundVolume() {
	return sound_volume_;
}

void SettingsHandler::setSoundVolume(float volume) {
	sound_volume_ = volume;
}

int SettingsHandler::getCurrentAudioId()
{
	return current_audio_id_;
}

void SettingsHandler::setCurrentAudioId(int t)
{
	current_audio_id_ = t;
}

std::vector<int>& SettingsHandler::getMaxProgress()
{
	return max_progress_;
}
