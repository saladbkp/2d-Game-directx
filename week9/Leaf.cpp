#include "Leaf.h"
#include "Graphics.h"
#include <cmath>
#include "Polygon.h"
#include <ctime> // For random number generation

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

LEAF g_aLeaf;
LPDIRECT3DTEXTURE9 g_pTextureLeaf = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLeaf = NULL;

float gravity = 0.1f; // Gravity force
float windForce = 2.0f; // Wind force

// Initialize leaf vertices, texture, and properties
HRESULT InitLeaf(LPDIRECT3DDEVICE9 pDevice) {
    if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffLeaf, NULL))) {
        return E_FAIL;
    }

    VERTEX_2D* pVtx;
    g_pVtxBuffLeaf->Lock(0, 0, (void**)&pVtx, 0);

    D3DXCreateTextureFromFile(pDevice, ".\\Assets\\leaf.png", &g_pTextureLeaf);

    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize leaf properties
    g_aLeaf.fWidth = 30.0f; // Default size, change as needed
    g_aLeaf.fHeight = 30.0f; // Default size, change as needed
    g_aLeaf.pos = D3DXVECTOR3(static_cast<float>(rand() % SCREEN_WIDTH), 50.0f + g_aLeaf.fHeight / 2, 0.0f);
    g_aLeaf.bActive = false;
    g_aLeaf.fallSpeed = 0.0f; // Initial falling speed

    pVtx[0].pos = D3DXVECTOR3(g_aLeaf.pos.x - g_aLeaf.fWidth / 2, g_aLeaf.pos.y - g_aLeaf.fHeight / 2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(g_aLeaf.pos.x + g_aLeaf.fWidth / 2, g_aLeaf.pos.y - g_aLeaf.fHeight / 2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(g_aLeaf.pos.x - g_aLeaf.fWidth / 2, g_aLeaf.pos.y + g_aLeaf.fHeight / 2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(g_aLeaf.pos.x + g_aLeaf.fWidth / 2, g_aLeaf.pos.y + g_aLeaf.fHeight / 2, 0.0f);

    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

    g_pVtxBuffLeaf->Unlock();

    // Set render states for transparency
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

    return S_OK;
}

// Free resources
void UninitLeaf() {
    if (g_pVtxBuffLeaf) {
        g_pVtxBuffLeaf->Release();
        g_pVtxBuffLeaf = NULL;
    }
    if (g_pTextureLeaf) {
        g_pTextureLeaf->Release();
        g_pTextureLeaf = NULL;
    }
}

// Update leaf position with gravity and wind force
void UpdateLeaf() {
    //if (!g_aLeaf.bActive) return;

    // Apply gravity and wind force
    g_aLeaf.fallSpeed += gravity;
    g_aLeaf.pos.y += g_aLeaf.fallSpeed;
    g_aLeaf.pos.x += windForce;

    // If leaf goes off-screen, reposition it to the top with a random x position
    if (g_aLeaf.pos.y - g_aLeaf.fHeight / 2 > SCREEN_HEIGHT) {
        g_aLeaf.pos.x = static_cast<float>(rand() % SCREEN_WIDTH);
        g_aLeaf.pos.y = 50.0f + g_aLeaf.fHeight / 2;
        g_aLeaf.fallSpeed = 0.0f; // Reset falling speed
    }

    VERTEX_2D* pVtx;
    g_pVtxBuffLeaf->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].pos = D3DXVECTOR3(g_aLeaf.pos.x - g_aLeaf.fWidth / 2, g_aLeaf.pos.y - g_aLeaf.fHeight / 2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(g_aLeaf.pos.x + g_aLeaf.fWidth / 2, g_aLeaf.pos.y - g_aLeaf.fHeight / 2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(g_aLeaf.pos.x - g_aLeaf.fWidth / 2, g_aLeaf.pos.y + g_aLeaf.fHeight / 2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(g_aLeaf.pos.x + g_aLeaf.fWidth / 2, g_aLeaf.pos.y + g_aLeaf.fHeight / 2, 0.0f);

    g_pVtxBuffLeaf->Unlock();
}

// Draw the leaf
void DrawLeaf(LPDIRECT3DDEVICE9 pDevice) {
    if (!g_aLeaf.bActive) return;

    pDevice->SetFVF(FVF_VERTEX_2D);
    pDevice->SetTexture(0, g_pTextureLeaf);
    pDevice->SetStreamSource(0, g_pVtxBuffLeaf, 0, sizeof(VERTEX_2D));
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

// Get a reference to the leaf
LEAF* GetLeaf() {
    return &g_aLeaf;
}

// Check collision with player (polygon)
bool CheckCollisionWithPlayerLeaf(const D3DXVECTOR3& playerPos, float playerWidth, float playerHeight) {
    if (!g_aLeaf.bActive) return false;

    float leafLeft = g_aLeaf.pos.x - g_aLeaf.fWidth / 2;
    float leafRight = g_aLeaf.pos.x + g_aLeaf.fWidth / 2;
    float leafTop = g_aLeaf.pos.y - g_aLeaf.fHeight / 2;
    float leafBottom = g_aLeaf.pos.y + g_aLeaf.fHeight / 2;

    float playerLeft = playerPos.x - playerWidth / 2;
    float playerRight = playerPos.x + playerWidth / 2;
    float playerTop = playerPos.y - playerHeight / 2;
    float playerBottom = playerPos.y + playerHeight / 2;

    // Check if rectangles overlap
    return !(leafLeft > playerRight || leafRight < playerLeft || leafTop > playerBottom || leafBottom < playerTop);
}
