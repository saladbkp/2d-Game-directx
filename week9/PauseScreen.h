#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include <d3d9.h>
#include <d3dx9.h>
#include <stdexcept>

class PauseScreen {
public:
    PauseScreen();  // Default constructor
    ~PauseScreen(); // Destructor

    void Init(LPDIRECT3DDEVICE9 d3ddev);
    void Render(LPDIRECT3DDEVICE9 d3ddev);
    void Cleanup();

private:
    LPDIRECT3DTEXTURE9 pauseTexture;
    LPD3DXSPRITE spriteHandler;

    void CreateSprite(LPDIRECT3DDEVICE9 d3ddev);
};

#endif // PAUSESCREEN_H
