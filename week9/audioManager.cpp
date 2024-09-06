#include "AudioManager.h"
#include <mmsystem.h>
#include <fstream>

AudioManager::AudioManager() : directSound(nullptr), primaryBuffer(nullptr), secondaryBuffer(nullptr) {}

AudioManager::~AudioManager() {
    Cleanup();
}

bool AudioManager::Init(HWND hwnd) {
    HRESULT result;

    // Initialize DirectSound
    result = DirectSoundCreate8(NULL, &directSound, NULL);
    if (FAILED(result)) return false;

    result = directSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
    if (FAILED(result)) return false;

    DSBUFFERDESC bufferDesc;
    memset(&bufferDesc, 0, sizeof(DSBUFFERDESC));
    bufferDesc.dwSize = sizeof(DSBUFFERDESC);
    bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;

    // Create a primary buffer
    result = directSound->CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL);
    if (FAILED(result)) return false;

    return true;
}

bool AudioManager::LoadWaveFile(LPCSTR filename) {
    // Open the wave file
    FILE* filePtr;
    fopen_s(&filePtr, filename, "rb");
    if (!filePtr) return false;

    // Read wave header
    WAVEFORMATEX waveFormat;
    fseek(filePtr, 20, SEEK_SET);
    fread(&waveFormat, sizeof(WAVEFORMATEX), 1, filePtr);

    // Read data size
    fseek(filePtr, 40, SEEK_SET);
    DWORD dataSize;
    fread(&dataSize, sizeof(DWORD), 1, filePtr);

    // Allocate memory for wave data
    BYTE* waveData = new BYTE[dataSize];
    fread(waveData, dataSize, 1, filePtr);

    fclose(filePtr);

    // Set buffer description
    DSBUFFERDESC bufferDesc;
    memset(&bufferDesc, 0, sizeof(bufferDesc));
    bufferDesc.dwSize = sizeof(DSBUFFERDESC);
    bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
    bufferDesc.dwBufferBytes = dataSize;
    bufferDesc.lpwfxFormat = &waveFormat;

    // Create the secondary buffer (temporary LPDIRECTSOUNDBUFFER)
    LPDIRECTSOUNDBUFFER tempBuffer = nullptr;
    HRESULT result = directSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
    if (FAILED(result)) return false;

    // QueryInterface to get the LPDIRECTSOUNDBUFFER8
    result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&secondaryBuffer);
    if (FAILED(result)) {
        tempBuffer->Release();  // Release tempBuffer if QueryInterface fails
        return false;
    }

    tempBuffer->Release();  // Release tempBuffer after successfully querying

    // Copy the wave data into the buffer
    VOID* bufferPtr;
    DWORD bufferSize;
    secondaryBuffer->Lock(0, dataSize, &bufferPtr, &bufferSize, NULL, NULL, 0);
    memcpy(bufferPtr, waveData, dataSize);
    secondaryBuffer->Unlock(bufferPtr, bufferSize, NULL, 0);

    delete[] waveData;
    return true;
}

void AudioManager::PlayBackgroundMusic() {
    if (secondaryBuffer) {
        secondaryBuffer->SetCurrentPosition(0);
        secondaryBuffer->SetVolume(DSBVOLUME_MAX);
        secondaryBuffer->Play(0, 0, DSBPLAY_LOOPING);  // Loop the background music
    }
}

void AudioManager::Cleanup() {
    if (secondaryBuffer) {
        secondaryBuffer->Release();
        secondaryBuffer = nullptr;
    }
    if (primaryBuffer) {
        primaryBuffer->Release();
        primaryBuffer = nullptr;
    }
    if (directSound) {
        directSound->Release();
        directSound = nullptr;
    }
}
