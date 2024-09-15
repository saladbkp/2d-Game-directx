#pragma once
#include <d3dx9.h>

struct CACTUS {
    D3DXVECTOR3 pos; // Position of the cactus
    float fWidth;     // Width of the cactus
    float fHeight;    // Height of the cactus
    bool bActive;       // Is the cactus active?
};

HRESULT InitCactus(LPDIRECT3DDEVICE9 pDevice);
void UninitCactus();
void UpdateCactus();
void DrawCactus(LPDIRECT3DDEVICE9 pDevice);
CACTUS* GetCactus();
bool CheckCollisionWithPlayer(const D3DXVECTOR3& playerPos, float playerWidth, float playerHeight);
