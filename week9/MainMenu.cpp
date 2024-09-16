#include "MainMenu.h"
#include <d3dx9.h>

MainMenu::MainMenu() : startClicked(false), exitClicked(false), startButtonTexture(nullptr), exitButtonTexture(nullptr), bgTexture(nullptr), font(nullptr) {}

void MainMenu::Init(LPDIRECT3DDEVICE9 d3ddev) {
    // Load textures for background, start, and exit buttons
    D3DXCreateTextureFromFile(d3ddev, "Assets\\bg1.png", &bgTexture);
    D3DXCreateTextureFromFile(d3ddev, "Assets\\start-icon.png", &startButtonTexture);
    D3DXCreateTextureFromFile(d3ddev, "Assets\\quit-icon.png", &exitButtonTexture);

    // Adjust button positions and sizes
    startButtonRect = { 250, 350, 850, 570 };  // Start button (lower position, smaller height)
    exitButtonRect = { 700, 50, 1000, 190 };   // Exit button (closer to the start button)

    // Set up text rectangle (position)
    //menuTextRect = { 250, 150, 450, 200 };     // Centered above the buttons

    // Create font for rendering text
    D3DXCreateFont(d3ddev, 40, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &font);

    // Initialize audio manager
    /*if (audioManager.Init(GetForegroundWindow())) {
        audioManager.LoadWaveFile("Assets\\bg.wav");
        audioManager.PlayBackgroundMusic();
    }*/
}

void MainMenu::Render(LPDIRECT3DDEVICE9 d3ddev) {
    // Create a sprite interface
    LPD3DXSPRITE sprite;
    D3DXCreateSprite(d3ddev, &sprite);

    // Begin the sprite rendering process
    sprite->Begin(D3DXSPRITE_ALPHABLEND);

    // Render the background image
    D3DXVECTOR3 bgPos(0, 0, 0);  // Assume background fills the entire screen
    sprite->Draw(bgTexture, nullptr, nullptr, &bgPos, D3DCOLOR_XRGB(255, 255, 255));

    // Render the start button
    D3DXVECTOR3 startPos((float)startButtonRect.left, (float)startButtonRect.top, 0);
    sprite->Draw(startButtonTexture, nullptr, nullptr, &startPos, D3DCOLOR_XRGB(255, 255, 255));

    // Render the exit button
    D3DXVECTOR3 exitPos((float)exitButtonRect.left, (float)exitButtonRect.top, 0);
    sprite->Draw(exitButtonTexture, nullptr, nullptr, &exitPos, D3DCOLOR_XRGB(255, 255, 255));

    // End the sprite rendering process
    sprite->End();

    // Render the menu text
    /*RECT textRect = menuTextRect;
    font->DrawText(nullptr, TEXT("Main Menu"), -1, &textRect, DT_CENTER | DT_VCENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));*/

    // Release the sprite
    sprite->Release();
}

void MainMenu::HandleInput(POINT mousePos, bool isClick) {
    // Reset clicks each frame
    startClicked = false;
    exitClicked = false;

    if (isClick) {
        // Check if the start button is clicked
        if (mousePos.x >= startButtonRect.left && mousePos.x <= startButtonRect.right &&
            mousePos.y >= startButtonRect.top && mousePos.y <= startButtonRect.bottom) {
            startClicked = true;
        }

        // Check if the exit button is clicked
        if (mousePos.x >= exitButtonRect.left && mousePos.x <= exitButtonRect.right &&
            mousePos.y >= exitButtonRect.top && mousePos.y <= exitButtonRect.bottom) {
            exitClicked = true;
        }
    }
}

bool MainMenu::IsStartClicked() {
    return startClicked;
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
    if (exitButtonTexture) {
        exitButtonTexture->Release();
        exitButtonTexture = nullptr;
    }
    if (font) {
        font->Release();
        font = nullptr;
    }

    audioManager.Cleanup();  // Clean up audio resources
}