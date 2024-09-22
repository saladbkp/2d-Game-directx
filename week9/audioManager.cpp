#include "AudioManager.h"
#include "SettingsManager.h"
#include <string>

AudioManager::AudioManager() {}

AudioManager::~AudioManager() {
    Cleanup();
}

void AudioManager::InitializeAudio() {
    result = FMOD::System_Create(&system);
    result = system->init(32, FMOD_INIT_NORMAL, extradriverdate);
}

void AudioManager::LoadSound() {
    result = system->createSound("Assets/Sound/bgmusic.wav", FMOD_DEFAULT, 0, &sound);
    result = sound->setMode(FMOD_LOOP_NORMAL);
    sounds["Background music"] = sound;

    result = system->createSound("Assets/Sound/Click sound.wav", FMOD_DEFAULT, 0, &sound);
    result = sound->setMode(FMOD_LOOP_OFF);
    sounds["Click sound"] = sound;

    result = system->createStream("Assets/Sound/Bounce sound 2.wav", FMOD_DEFAULT, 0, &sound);
    result = sound->setMode(FMOD_LOOP_OFF);
    sounds["Bounce sound 2"] = sound;

    result = system->createStream("Assets/Sound/Jump sound.wav", FMOD_DEFAULT, 0, &sound);
    result = sound->setMode(FMOD_LOOP_OFF);
    sounds["Jump sound"] = sound;
}

void AudioManager::PlaySoundTrack(SettingsManager* settings) {
    if (sounds.find("Background music") != sounds.end()) {
        result = system->playSound(sounds["Background music"], 0, true, &bgmChannel);
        bgmChannel->setVolume(settings->GetBGMVolume());  // Apply BGM volume from settings
        bgmChannel->setPaused(false);
    }
}

void AudioManager::PlaySound1(std::string soundName, float frequency, SettingsManager* settings) {
    if (sounds.find(soundName) != sounds.end()) {
        result = system->playSound(sounds[soundName], 0, true, &sfxChannel);
        sfxChannel->setFrequency(frequency);
        sfxChannel->setVolume(settings->GetSFXVolume());  // Apply SFX volume from settings
        sfxChannel->setPaused(false);
    }
}

void AudioManager::UpdateVolume(SettingsManager* settings) {
    for (auto& soundPair : sounds) {
        if (bgmChannel) {
            bgmChannel->setVolume(settings->GetBGMVolume());
        }
        if (sfxChannel) {
            sfxChannel->setVolume(settings->GetSFXVolume());
        }
    }
}

void AudioManager::Cleanup() {
    for (auto& soundPair : sounds) {
        soundPair.second->release();
    }

    system->close();
    system->release();
    system = nullptr;
}
