#include "Cactus.h"
#include "Graphics.h"
#include <cmath>
#include "Polygon.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

CACTUS g_aCactus;
LPDIRECT3DTEXTURE9 g_pTextureCactus = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCactus = NULL;

float cactusSpeed = 5.0f; // Speed at which the cactus moves to the left

// Initialize cactus vertices, texture, and properties
HRESULT InitCactus(LPDIRECT3DDEVICE9 pDevice) {
    if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffCactus, NULL))) {
        return E_FAIL;
    }

    VERTEX_2D* pVtx;
    g_pVtxBuffCactus->Lock(0, 0, (void**)&pVtx, 0);

    D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\cactus.png", &g_pTextureCactus);

    g_aCactus.fWidth = 50.0f;
    g_aCactus.fHeight = 100.0f;
    g_aCactus.pos = D3DXVECTOR3(SCREEN_WIDTH + g_aCactus.fWidth / 2, SCREEN_HEIGHT - g_aCactus.fHeight / 2, 0.0f);
    g_aCactus.bActive = false;

    pVtx[0].pos = D3DXVECTOR3(g_aCactus.pos.x - g_aCactus.fWidth / 2, g_aCactus.pos.y - g_aCactus.fHeight / 2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(g_aCactus.pos.x + g_aCactus.fWidth / 2, g_aCactus.pos.y - g_aCactus.fHeight / 2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(g_aCactus.pos.x - g_aCactus.fWidth / 2, g_aCactus.pos.y + g_aCactus.fHeight / 2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(g_aCactus.pos.x + g_aCactus.fWidth / 2, g_aCactus.pos.y + g_aCactus.fHeight / 2, 0.0f);

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

    g_pVtxBuffCactus->Unlock();

    // Set render states for transparency
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

    return S_OK;
}

// Free resources
void UninitCactus() {
    if (g_pVtxBuffCactus) {
        g_pVtxBuffCactus->Release();
        g_pVtxBuffCactus = NULL;
    }
    if (g_pTextureCactus) {
        g_pTextureCactus->Release();
        g_pTextureCactus = NULL;
    }
}

// Update cactus position
void UpdateCactus() {
    if (!g_aCactus.bActive) return;

    // Move the cactus to the left
    g_aCactus.pos.x -= cactusSpeed;

    // If cactus goes off-screen, reposition it to the right side
    if (g_aCactus.pos.x + g_aCactus.fWidth / 2 < 0) {
        g_aCactus.pos.x = SCREEN_WIDTH + g_aCactus.fWidth / 2;
    }

    VERTEX_2D* pVtx;
    g_pVtxBuffCactus->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].pos = D3DXVECTOR3(g_aCactus.pos.x - g_aCactus.fWidth / 2, g_aCactus.pos.y - g_aCactus.fHeight / 2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(g_aCactus.pos.x + g_aCactus.fWidth / 2, g_aCactus.pos.y - g_aCactus.fHeight / 2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(g_aCactus.pos.x - g_aCactus.fWidth / 2, g_aCactus.pos.y + g_aCactus.fHeight / 2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(g_aCactus.pos.x + g_aCactus.fWidth / 2, g_aCactus.pos.y + g_aCactus.fHeight / 2, 0.0f);

    g_pVtxBuffCactus->Unlock();
}

// Draw the cactus
void DrawCactus(LPDIRECT3DDEVICE9 pDevice) {
    if (!g_aCactus.bActive) return;

    pDevice->SetFVF(FVF_VERTEX_2D);
    pDevice->SetTexture(0, g_pTextureCactus);
    pDevice->SetStreamSource(0, g_pVtxBuffCactus, 0, sizeof(VERTEX_2D));
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

// Get a reference to the cactus
CACTUS* GetCactus() {
    return &g_aCactus;
}

// Check collision with player (polygon)
bool CheckCollisionWithPlayer(const D3DXVECTOR3& playerPos, float playerWidth, float playerHeight) {
    if (!g_aCactus.bActive) return false;

    float cactusLeft = g_aCactus.pos.x - g_aCactus.fWidth / 2;
    float cactusRight = g_aCactus.pos.x + g_aCactus.fWidth / 2;
    float cactusTop = g_aCactus.pos.y - g_aCactus.fHeight / 2;
    float cactusBottom = g_aCactus.pos.y + g_aCactus.fHeight / 2;

    float playerLeft = playerPos.x - playerWidth / 2;
    float playerRight = playerPos.x + playerWidth / 2;
    float playerTop = playerPos.y - playerHeight / 2;
    float playerBottom = playerPos.y + playerHeight / 2;

    if (cactusRight < playerLeft || cactusLeft > playerRight ||
        cactusBottom < playerTop || cactusTop > playerBottom) {
        return false; // No collision
    }

    return true; // Collision detected
}
