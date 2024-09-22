#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "fmod.hpp"
#include "SettingsManager.h"
#include <string>
#include <map>

class AudioManager {
public:
    FMOD::System* system; // Virtual Soundcard
    std::map<std::string, FMOD::Sound*> sounds; // Store multiple sound files
    FMOD::Sound* sound;
    FMOD::Channel* bgmChannel = 0; // Channel where a sound will be assigned to
    FMOD::Channel* sfxChannel = 0; // Channel where a sound will be assigned to
    FMOD_RESULT result; // Error code
    void* extradriverdate = 0; // Unnecessary

    AudioManager();
    ~AudioManager();

    void InitializeAudio();
    void LoadSound();
    void PlaySoundTrack(SettingsManager* settings);
    void PlaySound1(std::string soundName, float frequency, SettingsManager* settings);
    void UpdateVolume(SettingsManager* settings);
    void Cleanup();

private:
};

#endif