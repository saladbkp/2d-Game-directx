#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <d3d9.h>
#include <d3dx9.h>

class SplashScreen {
public:
    SplashScreen();
    ~SplashScreen();

    bool Init(LPDIRECT3DDEVICE9 d3ddev, const wchar_t* filePath);
    void Render(LPDIRECT3DDEVICE9 d3ddev);
    void Cleanup();

private:
    LPDIRECT3DTEXTURE9 splashImage;  // The texture for the splash screen
    LPD3DXSPRITE sprite;             // Sprite to draw the texture
    int width;                       // Width of the splash image
    int height;                      // Height of the splash image
};

#endif
