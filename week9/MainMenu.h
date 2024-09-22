#ifndef MAINMENU_H
#define MAINMENU_H

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>

class MainMenu {
private:
    LPDIRECT3DTEXTURE9 bgTexture;
    LPDIRECT3DTEXTURE9 startButtonTexture;
    LPDIRECT3DTEXTURE9 settingsButtonTexture;
    LPDIRECT3DTEXTURE9 exitButtonTexture;
    RECT bgRect;
    RECT startButtonRect;
    RECT settingsButtonRect;
    RECT exitButtonRect;
    D3DXVECTOR3 bgPos;
    D3DXVECTOR3 startButtonPos;
    D3DXVECTOR3 settingsButtonPos;
    D3DXVECTOR3 exitButtonPos;
    bool startClicked;
    bool settingsClicked;
    bool exitClicked;


public:
    MainMenu();
    void Init(LPDIRECT3DDEVICE9 d3ddev);
    void Render(LPDIRECT3DDEVICE9 d3ddev);
    void HandleInput(POINT mousePos, bool isClick);
    bool IsStartClicked();
    bool IsSettingsClicked();
    bool IsExitClicked();
    void Cleanup();
};

#endif
