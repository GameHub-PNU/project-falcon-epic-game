#pragma once

class SettingsHandler
{
public:
	static float getSoundVolume();

	static void setSoundVolume(float volume);

	static int getCurrentAudioId();
	static void setCurrentAudioId(int t);
private:
	inline static float sound_volume_ = 0.5f;
	inline static int current_audio_id_ = -1;
};

