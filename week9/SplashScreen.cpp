#include "SplashScreen.h"

SplashScreen::SplashScreen() : splashImage(nullptr), sprite(nullptr) {}
SplashScreen::~SplashScreen() {}

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
        RECT splashRect{0, 0, 900, 700};
        D3DXVECTOR3 splashPosition(0, 0, 0);
        sprite->Draw(splashImage, &splashRect, nullptr, &splashPosition, D3DCOLOR_XRGB(255, 255, 255));

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
