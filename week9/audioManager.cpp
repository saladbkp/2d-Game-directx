#include "AudioManager.h"
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
    result = system->createSound("Assets/Sound/bg.wav", FMOD_DEFAULT, 0, &sound);
    result = sound->setMode(FMOD_LOOP_NORMAL);
    sounds["Background music"] = sound;

    result = system->createSound("Assets/Sound/Boom.wav", FMOD_DEFAULT, 0, &sound);
    result = sound->setMode(FMOD_LOOP_OFF);
    sounds["Boom"] = sound;

    result = system->createStream("Assets/Sound/Bounce sound 2.wav", FMOD_DEFAULT, 0, &sound);
    result = sound->setMode(FMOD_LOOP_OFF);
    sounds["Bounce sound 2"] = sound;
}

void AudioManager::PlaySoundTrack() {
    if (sounds.find("Background music") != sounds.end()) {
        result = system->playSound(sounds["Background music"], 0, true, &channel);
        channel->setVolume(0.5);
        channel->setPaused(false);
    }
}

void AudioManager::PlaySound1(std::string soundName, float frequency) {
    if (sounds.find(soundName) != sounds.end()) {
        result = system->playSound(sounds[soundName], 0, true, &channel);
        channel->setFrequency(frequency);
        channel->setPan(0);
        channel->setVolume(1);
        channel->setPaused(false);
    }
}

void AudioManager::SetVolume(std::string soundName) {

}

void AudioManager::Cleanup() {
    for (auto& soundPair : sounds) {
        soundPair.second->release();
    }

    system->close();
    system->release();
}
