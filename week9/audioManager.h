#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "fmod.hpp"
#include <string>
#include <map>

class AudioManager {
public:
    FMOD::System* system; // Virtual Soundcard
    std::map<std::string, FMOD::Sound*> sounds; // Store multiple sound files
    FMOD::Sound* sound;
    FMOD::Channel* channel = 0; // Channel where a sound will be assigned to
    FMOD_RESULT result; // Error code
    void* extradriverdate = 0; // Unnecessary

    AudioManager();
    ~AudioManager();

    void InitializeAudio();
    void LoadSound();
    void PlaySound1(std::string soundName, float frequency);
    void PlaySoundTrack();
    void SetVolume(std::string soundName);
    void Cleanup();

private:
};

#endif

