#include "background.h"
#include <stdexcept>

// Constructor to initialize variables
ScrollingBackground::ScrollingBackground(LPDIRECT3DDEVICE9 d3ddev)
    : offsetX(0), offsetY(0), screenWidth(800), screenHeight(600)
{
    sprite_handler = nullptr;
    back_image = nullptr;
}

// Destructor
ScrollingBackground::~ScrollingBackground()
{
    if (back_image) back_image->Release();
    if (sprite_handler) sprite_handler->Release();
}

// Initialization function: loads the texture and initializes the sprite handler
void ScrollingBackground::Init(LPDIRECT3DDEVICE9 d3ddev, const std::string& texturePath, int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    // Initialize the sprite handler
    D3DXCreateSprite(d3ddev, &sprite_handler);

    // Load the background image as a texture
    D3DXIMAGE_INFO info;
    HRESULT hr = D3DXGetImageInfoFromFile(texturePath.c_str(), &info);
    if (FAILED(hr))
        throw std::runtime_error("Failed to load texture info");

    textureWidth = info.Width;
    textureHeight = info.Height;

    hr = D3DXCreateTextureFromFileEx(d3ddev, texturePath.c_str(), textureWidth, textureHeight,
        D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
        D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255),
        &info, NULL, &back_image);
    if (FAILED(hr))
        throw std::runtime_error("Failed to load texture");

    // Set initial position
    position = D3DXVECTOR3(0, 0, 0);
}

// Update the offset based on movement
void ScrollingBackground::Update(float deltaX, float deltaY)
{
    offsetX += static_cast<int>(deltaX);
    offsetY += static_cast<int>(deltaY);

    // Wrap the offset values to create infinite scrolling effect
    if (offsetX >= textureWidth)
        offsetX -= textureWidth;
    if (offsetX < 0)
        offsetX += textureWidth;
    if (offsetY >= textureHeight)
        offsetY -= textureHeight;
    if (offsetY < 0)
        offsetY += textureHeight;
}

// Render function: draws the background by tiling
void ScrollingBackground::Render(LPDIRECT3DDEVICE9 d3ddev)
{
    sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

    // Draw the background in 4 quadrants (tiles)
    DrawTile(-offsetX, -offsetY, d3ddev);                          // Top-left
    DrawTile(textureWidth - offsetX, -offsetY, d3ddev);           // Top-right
    DrawTile(-offsetX, textureHeight - offsetY, d3ddev);          // Bottom-left
    DrawTile(textureWidth - offsetX, textureHeight - offsetY, d3ddev); // Bottom-right

    sprite_handler->End();
}

// Helper function for drawing a single tile at a specified position
void ScrollingBackground::DrawTile(int x, int y, LPDIRECT3DDEVICE9 d3ddev)
{
    position.x = static_cast<float>(x);
    position.y = static_cast<float>(y);

    rct.left = 0;
    rct.right = textureWidth;
    rct.top = 0;
    rct.bottom = textureHeight;

    sprite_handler->Draw(back_image, &rct, NULL, &position, 0xFFFFFFFF);
}
