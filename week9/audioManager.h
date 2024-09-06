#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <dsound.h>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    bool Init(HWND hwnd);
    bool LoadWaveFile(LPCSTR filename);
    void PlayBackgroundMusic();
    void Cleanup();

private:
    LPDIRECTSOUND8 directSound;
    LPDIRECTSOUNDBUFFER primaryBuffer;
    LPDIRECTSOUNDBUFFER secondaryBuffer;
};

#endif