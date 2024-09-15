#pragma once

#include <d3dx9.h>
#include <string>

class ScrollingBackground
{
public:
    ScrollingBackground(LPDIRECT3DDEVICE9 d3ddev);
    ~ScrollingBackground();

    void Init(LPDIRECT3DDEVICE9 d3ddev, const std::string& texturePath, int screenWidth, int screenHeight);
    void Update(float deltaX, float deltaY);
    void Render(LPDIRECT3DDEVICE9 d3ddev);

private:
    void DrawTile(int x, int y, LPDIRECT3DDEVICE9 d3ddev);

    LPD3DXSPRITE sprite_handler;      // Sprite handler for drawing the background
    LPDIRECT3DTEXTURE9 back_image;    // Texture for the background
    D3DXVECTOR3 position;             // 3D vector for the position
    RECT rct;                         // Rectangle for texture clipping
    int offsetX, offsetY;             // X and Y offsets for scrolling
    int textureWidth, textureHeight;  // Width and height of the texture
    int screenWidth, screenHeight;    // Screen dimensions
};
