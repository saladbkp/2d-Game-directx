#pragma once
#include <d3dx9.h>

struct LEAF {
    D3DXVECTOR3 pos; // Position of the leaf
    float fWidth;    // Width of the leaf
    float fHeight;   // Height of the leaf
    bool bActive;    // Is the leaf active?
    float fallSpeed; // Speed at which the leaf falls, influenced by size
};

HRESULT InitLeaf(LPDIRECT3DDEVICE9 pDevice);
void UninitLeaf();
void UpdateLeaf();
void DrawLeaf(LPDIRECT3DDEVICE9 pDevice);
LEAF* GetLeaf();
bool CheckCollisionWithPlayerLeaf(const D3DXVECTOR3& playerPos, float playerWidth, float playerHeight);
