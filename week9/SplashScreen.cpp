#include "SplashScreen.h"

SplashScreen::SplashScreen() : splashImage(nullptr), sprite(nullptr) {}
SplashScreen::~SplashScreen() {
    // If you have any allocated resources, release them here
}
bool SplashScreen::Init(LPDIRECT3DDEVICE9 d3ddev, LPCWSTR imagePath) {
    // Load the texture for splash screen
    if (FAILED(D3DXCreateTextureFromFileW(d3ddev, imagePath, &splashImage))) {
        return false;
    }

    // Create sprite object
    if (FAILED(D3DXCreateSprite(d3ddev, &sprite))) {
        return false;
    }

    return true;
}

void SplashScreen::Render(LPDIRECT3DDEVICE9 d3ddev) {
    if (sprite && splashImage) {
        sprite->Begin(D3DXSPRITE_ALPHABLEND);

        // Render the splash image
        D3DXVECTOR3 position(0, 0, 0); // Top-left corner
        sprite->Draw(splashImage, nullptr, nullptr, &position, D3DCOLOR_XRGB(255, 255, 255));

        sprite->End();
    }
}

void SplashScreen::Cleanup() {
    if (splashImage) {
        splashImage->Release();
        splashImage = nullptr;
    }

    if (sprite) {
        sprite->Release();
        sprite = nullptr;
    }
}
