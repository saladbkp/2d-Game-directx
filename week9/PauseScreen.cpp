#include "PauseScreen.h"

// Default constructor
PauseScreen::PauseScreen()
    : pauseTexture(nullptr), spriteHandler(nullptr) {}

// Destructor
PauseScreen::~PauseScreen() {
    Cleanup();
}

// Initialization function
void PauseScreen::Init(LPDIRECT3DDEVICE9 d3ddev) {
    CreateSprite(d3ddev);
}

// Create sprite and load texture for the pause screen
void PauseScreen::CreateSprite(LPDIRECT3DDEVICE9 d3ddev) {
    HRESULT hr = D3DXCreateTextureFromFile(d3ddev, "Assets\\pandaerror.png", &pauseTexture);
    if (FAILED(hr)) {
        MessageBox(NULL, "Could not load pause.png", "Error", MB_OK);
        return;
    }

    hr = D3DXCreateSprite(d3ddev, &spriteHandler);
    if (FAILED(hr)) {
        MessageBox(NULL, "Failed to create sprite handler!", "Error", MB_OK);
        pauseTexture->Release();
        pauseTexture = nullptr;
    }
}

// Render function for the pause screen
void PauseScreen::Render(LPDIRECT3DDEVICE9 d3ddev) {
    if (spriteHandler && pauseTexture) {
        spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

        D3DXVECTOR3 position(0.0f, 0.0f, 0.0f); // Center position (you can adjust this)
        RECT rct = { 0, 0, 800, 600 }; // Assuming your texture is 800x600

        spriteHandler->Draw(pauseTexture, &rct, NULL, &position, 0xFFFFFFFF);

        spriteHandler->End();
    }
}

// Cleanup function to release resources
void PauseScreen::Cleanup() {
    if (pauseTexture) {
        pauseTexture->Release();
        pauseTexture = nullptr;
    }
    if (spriteHandler) {
        spriteHandler->Release();
        spriteHandler = nullptr;
    }
}
