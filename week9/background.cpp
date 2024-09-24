#include "background.h"
#include <stdexcept>

// Default constructor
ScrollingBackground::ScrollingBackground()
    : offsetX1(0), offsetX2(0), offsetX3(0), screenWidth(800), screenHeight(600)
{
    sprite_handler = nullptr;
}
// Constructor to initialize variables
ScrollingBackground::ScrollingBackground(LPDIRECT3DDEVICE9 d3ddev)
    : offsetX1(0), offsetX2(0), offsetX3(0), screenWidth(800), screenHeight(600)
{
    sprite_handler = nullptr;
    back_image1 = nullptr;
    back_image2 = nullptr;
    back_image3 = nullptr;
}

// Destructor
ScrollingBackground::~ScrollingBackground()
{
    // (back_image1) back_image1->Release();
    //if (back_image2) back_image2->Release();
    //if (back_image3) back_image3->Release();
    //if (sprite_handler) sprite_handler->Release();
}

void ScrollingBackground::Cleanup()
{
    if (back_image1) back_image1->Release();
    if (back_image2) back_image2->Release();
    if (back_image3) back_image3->Release();
    if (sprite_handler) sprite_handler->Release();
}

// Initialization function: loads the textures for all 3 layers
void ScrollingBackground::Init(LPDIRECT3DDEVICE9 d3ddev, const std::string& texturePath1, const std::string& texturePath2, const std::string& texturePath3, int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    // Initialize the sprite handler
    HRESULT hr = D3DXCreateSprite(d3ddev, &sprite_handler);
    //if (FAILED(hr)) {
    //    MessageBox(NULL, "Failed to create sprite handler!", "Error", MB_OK);
    //    sprite_handler = nullptr;
    //    return;  // If failed, stop further execution
    //}

    // Load all 3 background layers as textures
    try {
        LoadTexture(d3ddev, texturePath1, back_image1, textureWidth1, textureHeight1);
        LoadTexture(d3ddev, texturePath2, back_image2, textureWidth2, textureHeight2);
        LoadTexture(d3ddev, texturePath3, back_image3, textureWidth3, textureHeight3);
    }
    catch (const std::runtime_error& e) {
        MessageBox(NULL, e.what(), "Error", MB_OK);
        return;  // Handle texture loading failures
    }
}

// Helper function to load a texture
void ScrollingBackground::LoadTexture(LPDIRECT3DDEVICE9 d3ddev, const std::string& texturePath, LPDIRECT3DTEXTURE9& texture, int& width, int& height)
{
    D3DXIMAGE_INFO info;
    HRESULT hr = D3DXGetImageInfoFromFile(texturePath.c_str(), &info);
    if (FAILED(hr))
        throw std::runtime_error("Failed to load texture info");

    width = info.Width;
    height = info.Height;

    hr = D3DXCreateTextureFromFileEx(d3ddev, texturePath.c_str(), width, height,
        D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
        D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255),
        &info, NULL, &texture);
    if (FAILED(hr))
        throw std::runtime_error("Failed to load texture");
}

// Update function for scrolling based on player's movement
void ScrollingBackground::Update(float deltaX)
{
    float scrollSpeed1 = 0.5f;  // Slowest speed (farthest layer)
    float scrollSpeed2 = 0.8f;  // Medium speed (middle layer)
    float scrollSpeed3 = 1.0f;  // Fastest speed (closest layer)

    // Update offsets for each layer based on deltaX
    offsetX1 += deltaX * scrollSpeed1;
    offsetX2 += deltaX * scrollSpeed2;
    offsetX3 += deltaX * scrollSpeed3;

    // Wrap offsets to create infinite scrolling effect
    WrapOffset(offsetX1, textureWidth1);
    WrapOffset(offsetX2, textureWidth2);
    WrapOffset(offsetX3, textureWidth3);
}

// Helper function to wrap offsets for continuous scrolling
void ScrollingBackground::WrapOffset(int& offsetX, int textureWidth)
{
    if (offsetX >= textureWidth)
        offsetX -= textureWidth;
    if (offsetX < 0)
        offsetX += textureWidth;
}

// Render function: draws all 3 background layers
void ScrollingBackground::Render(LPDIRECT3DDEVICE9 d3ddev)
{
    if (sprite_handler) {
        sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

        // Render the 3 layers with independent offsets, using two tiles for each layer
        DrawTile(-offsetX1, 0, d3ddev, back_image1, textureWidth1, textureHeight1); // Farthest layer
        DrawTile(textureWidth1 - offsetX1, 0, d3ddev, back_image1, textureWidth1, textureHeight1); // Seamless tile

        DrawTile(-offsetX2, 0, d3ddev, back_image2, textureWidth2, textureHeight2); // Middle layer
        DrawTile(textureWidth2 - offsetX2, 0, d3ddev, back_image2, textureWidth2, textureHeight2); // Seamless tile

        DrawTile(-offsetX3, 0, d3ddev, back_image3, textureWidth3, textureHeight3); // Closest layer
        DrawTile(textureWidth3 - offsetX3, 0, d3ddev, back_image3, textureWidth3, textureHeight3); // Seamless tile

        sprite_handler->End();
    }    
}

// Helper function for drawing a single tile of a background layer
void ScrollingBackground::DrawTile(int x, int y, LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DTEXTURE9 texture, int textureWidth, int textureHeight)
{
    D3DXVECTOR3 position(static_cast<float>(x), static_cast<float>(y), 0.0f);
    position.y += 30;  // Offset to position the background as needed

    RECT rct;
    rct.left = 0;
    rct.right = textureWidth;
    rct.top = 0;

    // Adjust the height to exclude the bottom 50 pixels
    rct.bottom = textureHeight - 70;

    // Draw the tile with the specified texture, with the adjusted height
    sprite_handler->Draw(texture, &rct, NULL, &position, 0xFFFFFFFF);
}

// Code to handle player input (A and D keys)
void HandlePlayerMovement(ScrollingBackground *background)
{
    float deltaX = 0.0f;

    // Check for player input (left or right movement)
    if (GetAsyncKeyState(0x41) & 0x8000) // 'A' key pressed
    {
        deltaX = -5.0f; // Move left
    }
    else if (GetAsyncKeyState(0x44) & 0x8000) // 'D' key pressed
    {
        deltaX = 5.0f; // Move right
    }

    // Update the background based on the player's movement
    background->Update(deltaX);
}
