#include "SettingsManager.h"

SettingsManager::SettingsManager() : bgmVolume(1.0f), sfxVolume(1.0f) {} // Default volume set to 50%

// Getter and Setter methods for BGM volume
float SettingsManager::GetBGMVolume() const {
    return bgmVolume;
}

void SettingsManager::SetBGMVolume(float volume) {
    bgmVolume = volume;
}

// Getter and Setter methods for SFX volume
float SettingsManager::GetSFXVolume() const {
    return sfxVolume;
}

void SettingsManager::SetSFXVolume(float volume) {
    sfxVolume = volume;
}