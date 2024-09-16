#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class ScrollingBackground
{
public:
    // Constructor and Destructor
    ScrollingBackground(LPDIRECT3DDEVICE9 d3ddev);
    ~ScrollingBackground();

    // Initialization function to load textures for all three layers
    void Init(LPDIRECT3DDEVICE9 d3ddev, const std::string& texturePath1, const std::string& texturePath2, const std::string& texturePath3, int screenWidth, int screenHeight);

    // Update function to move the background
    void Update(float deltaX);

    // Render function to draw all layers
    void Render(LPDIRECT3DDEVICE9 d3ddev);

private:
    // Sprite handler for rendering
    LPD3DXSPRITE sprite_handler;

    // Texture for each background layer
    LPDIRECT3DTEXTURE9 back_image1;
    LPDIRECT3DTEXTURE9 back_image2;
    LPDIRECT3DTEXTURE9 back_image3;

    // Texture dimensions for each layer
    int textureWidth1, textureHeight1;
    int textureWidth2, textureHeight2;
    int textureWidth3, textureHeight3;

    // Screen dimensions
    int screenWidth;
    int screenHeight;

    // Offsets for scrolling each layer
    int offsetX1; // Farthest layer
    int offsetX2; // Middle layer
    int offsetX3; // Closest layer

    // Helper function to load a texture
    void LoadTexture(LPDIRECT3DDEVICE9 d3ddev, const std::string& texturePath, LPDIRECT3DTEXTURE9& texture, int& width, int& height);

    // Helper function to wrap offsets for continuous scrolling
    void WrapOffset(int& offsetX, int textureWidth);

    // Helper function to draw a single tile of a background layer
    void DrawTile(int x, int y, LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DTEXTURE9 texture, int textureWidth, int textureHeight);
};

// Function to handle player movement
void HandlePlayerMovement(ScrollingBackground& background);

#endif
