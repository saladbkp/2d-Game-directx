#ifndef MAINMENU_H
#define MAINMENU_H

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "AudioManager.h"

class MainMenu {
private:
    LPDIRECT3DTEXTURE9 startButtonTexture;
    LPDIRECT3DTEXTURE9 exitButtonTexture;
    LPDIRECT3DTEXTURE9 bgTexture;
    LPD3DXFONT font; // For rendering text
    RECT startButtonRect;
    RECT exitButtonRect;
    RECT menuTextRect;
    bool startClicked;
    bool exitClicked;
    AudioManager audioManager;  // Audio manager instance

public:
    MainMenu();
    void Init(LPDIRECT3DDEVICE9 d3ddev);
    void Render(LPDIRECT3DDEVICE9 d3ddev);
    void HandleInput(POINT mousePos, bool isClick);
    bool IsStartClicked();
    bool IsExitClicked();
    void Cleanup();
};

#endif
