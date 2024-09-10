#include "Graphics.h"
#include <d3d9.h> // DirectX 9

extern LPDIRECT3DDEVICE9 d3ddev; // Assume the device is initialized elsewhere

void Graphics::PutPixel(int x, int y, int r, int g, int b)
{
    D3DCOLOR color = D3DCOLOR_XRGB(r, g, b);

    // Use D3DRECT instead of RECT
    D3DRECT pixel = { x, y, x + 1, y + 1 };

    // Render the pixel using the device
    d3ddev->Clear(1, &pixel, D3DCLEAR_TARGET, color, 1.0f, 0);
}
