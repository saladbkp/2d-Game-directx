#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

class SettingsManager {
public:
    float bgmVolume;
    float sfxVolume;

    SettingsManager();

    // Getter and Setter for BGM volume
    float GetBGMVolume() const;
    void SetBGMVolume(float volume);

    // Getter and Setter for SFX volume
    float GetSFXVolume() const;
    void SetSFXVolume(float volume);
};

#endif