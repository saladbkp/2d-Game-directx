#include "MainMenu.h"
#include <d3dx9.h>

MainMenu::MainMenu() : startButtonTexture(nullptr), settingsButtonTexture(nullptr), exitButtonTexture(nullptr), bgTexture(nullptr),
startClicked(false), exitClicked(false) {}

void MainMenu::Init(LPDIRECT3DDEVICE9 d3ddev) {
    // Load textures for background, start, and exit buttons
    D3DXCreateTextureFromFile(d3ddev, "Assets\\mainmenubg.png", &bgTexture);
    D3DXCreateTextureFromFile(d3ddev, "Assets\\start-icon.png", &startButtonTexture);
    D3DXCreateTextureFromFile(d3ddev, "Assets\\setting-icon.png", &settingsButtonTexture);
    D3DXCreateTextureFromFile(d3ddev, "Assets\\quit-icon.png", &exitButtonTexture);

    bgRect = { 0, 0, 900, 700 };
    startButtonRect = { 0, 32, 128, 96 };
    settingsButtonRect = { 0, 0, 64, 64 };
    exitButtonRect = { 0, 0, 64, 64 };

    bgPos = D3DXVECTOR3(0, 0, 0);
    startButtonPos = D3DXVECTOR3(375, 400, 0);
    settingsButtonPos = D3DXVECTOR3(800, 100, 0);
    exitButtonPos = D3DXVECTOR3(800, 20, 0);
}

void MainMenu::Render(LPDIRECT3DDEVICE9 d3ddev) {
    // Create a sprite interface
    LPD3DXSPRITE sprite;
    D3DXCreateSprite(d3ddev, &sprite);

    // Begin the sprite rendering process
    sprite->Begin(D3DXSPRITE_ALPHABLEND);

    // Render the background image
    sprite->Draw(bgTexture, &bgRect, nullptr, &bgPos, D3DCOLOR_XRGB(255, 255, 255));

    // Render the start button
    sprite->Draw(startButtonTexture, nullptr, nullptr, &startButtonPos, D3DCOLOR_XRGB(255, 255, 255));

    // Render the settings button
    sprite->Draw(settingsButtonTexture, nullptr, nullptr, &settingsButtonPos, D3DCOLOR_XRGB(255, 255, 255));

    // Render the exit button
    sprite->Draw(exitButtonTexture, nullptr, nullptr, &exitButtonPos, D3DCOLOR_XRGB(255, 255, 255));

    // End the sprite rendering process
    sprite->End();

    sprite->Release();
}

void MainMenu::HandleInput(POINT mousePos, bool isClick) {
    // Reset clicks each frame
    startClicked = false;
    settingsClicked = false;
    exitClicked = false;

    if (isClick) {
        // Check if the start button is clicked
        if (mousePos.x >= startButtonPos.x && mousePos.x <= startButtonPos.x + startButtonRect.right &&
            mousePos.y >= startButtonPos.y && mousePos.y <= startButtonPos.y + startButtonRect.bottom) {
            startClicked = true;
        }
        // Check if the settings button is clicked
        if (mousePos.x >= settingsButtonPos.x && mousePos.x <= settingsButtonPos.x + settingsButtonRect.right &&
            mousePos.y >= settingsButtonPos.y && mousePos.y <= settingsButtonPos.y + settingsButtonRect.bottom ||
            mousePos.x >= settingsButtonPos.x && mousePos.x <= settingsButtonPos.x + (settingsButtonRect.right - settingsButtonRect.left) &&
            mousePos.y >= settingsButtonPos.y && mousePos.y <= settingsButtonPos.y + (settingsButtonRect.bottom - settingsButtonRect.top)) {
            settingsClicked = true;
        }
        // Check if the exit button is clicked
        if (mousePos.x >= exitButtonPos.x && mousePos.x <= exitButtonPos.x + exitButtonRect.right &&
            mousePos.y >= exitButtonPos.y && mousePos.y <= exitButtonPos.y + exitButtonRect.bottom) {
            exitClicked = true;
        }
    }
}

bool MainMenu::IsStartClicked() {
    return startClicked;
}

bool MainMenu::IsSettingsClicked() {
    return settingsClicked;
}

bool MainMenu::IsExitClicked() {
    return exitClicked;
}

void MainMenu::Cleanup() {
    if (bgTexture) {
        bgTexture->Release();
        bgTexture = nullptr;
    }
    if (startButtonTexture) {
        startButtonTexture->Release();
        startButtonTexture = nullptr;
    }
    if (settingsButtonTexture) {
        settingsButtonTexture->Release();
        settingsButtonTexture = nullptr;
    }
    if (exitButtonTexture) {
        exitButtonTexture->Release();
        exitButtonTexture = nullptr;
    }
}
