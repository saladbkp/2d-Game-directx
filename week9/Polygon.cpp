#include "Polygon.h"
#include "Graphics.h"
#include <d3dx9.h>
#include <dinput.h>
#include "Input.h"
#include <cmath>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

POLYGON g_aPolygon;
VERTEX_2D g_aVertex[4];
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;
D3DXVECTOR3 g_posPolygon;
D3DXVECTOR3 g_rotPolygon;
D3DXVECTOR3 g_movePolygon;
int g_nCounterAnim_Polygon = 0;
int g_nPatternAnim_Polygon = 0;
float animRow_Polygon = 1.0f;
float maxAnimX_Polygon = 4.0f;
float maxAnimY_Polygon = 1.0f;
float g_fLengthPolygon;
float g_fAnglePolygon;
float move_Polygon = 7.0f;
float runSpeed_Polygon = 2.0f;
int animMaxnum_Polygon = 4;
float startAnimY_Polygon = 0.0f;

// Define constants for gravity and jump
const float GRAVITY = 0.5f; // The rate at which gravity pulls the polygon down
const float JUMP_VELOCITY = -10.0f; // Initial velocity for jumping
bool isJumping = false; // To check if the polygon is currently jumping
float verticalVelocity = 0.0f; // The vertical velocity of the polygon

// Initialize polygon vertices, texture, and properties
HRESULT InitPolygon(LPDIRECT3DDEVICE9 pDevice) {
    if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPolygon, NULL))) {
        return E_FAIL;
    }

    VERTEX_2D* pVtx;
    g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

    D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\002.png", &g_pTexturePolygon);

    g_aPolygon.fWidth = 120.0f;
    g_aPolygon.fHeight = 120.0f;
    g_aPolygon.pos.x = 50.0f;
    g_aPolygon.pos.y = 500.0f;
    g_posPolygon = D3DXVECTOR3(g_aPolygon.pos.x, g_aPolygon.pos.y, 0.0f);
    g_aPolygon.bUse = true;
    g_aPolygon.bDoorUse = true;
    g_aPolygon.nLife = 4;

    g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    g_fLengthPolygon = sqrtf(g_aPolygon.fWidth * g_aPolygon.fWidth + g_aPolygon.fHeight * g_aPolygon.fHeight) * 0.5f;
    g_fAnglePolygon = atan2f(g_aPolygon.fWidth, g_aPolygon.fHeight) * 0.5f;

    pVtx[0].pos = D3DXVECTOR3(g_aPolygon.pos.x - sinf(g_fAnglePolygon + g_rotPolygon.z) * g_fLengthPolygon,
        g_aPolygon.pos.y - cosf(g_fAnglePolygon + g_rotPolygon.z) * g_fLengthPolygon, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(g_aPolygon.pos.x + sinf(g_fAnglePolygon - g_rotPolygon.z) * g_fLengthPolygon,
        g_aPolygon.pos.y - cosf(g_fAnglePolygon - g_rotPolygon.z) * g_fLengthPolygon, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(g_aPolygon.pos.x - sinf(g_fAnglePolygon - g_rotPolygon.z) * g_fLengthPolygon,
        g_aPolygon.pos.y + cosf(g_fAnglePolygon - g_rotPolygon.z) * g_fLengthPolygon, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(g_aPolygon.pos.x + sinf(g_fAnglePolygon + g_rotPolygon.z) * g_fLengthPolygon,
        g_aPolygon.pos.y + cosf(g_fAnglePolygon + g_rotPolygon.z) * g_fLengthPolygon, 0.0f);

    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Polygon, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Polygon);
    pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Polygon, 1.0f / maxAnimY_Polygon);

    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 128);
    pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 128);
    pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 128);
    pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 128);

    g_pVtxBuffPolygon->Unlock();

    // Set render states for transparency
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

    return S_OK;
}

// Free resources
void UninitPolygon() {
    if (g_pVtxBuffPolygon) {
        g_pVtxBuffPolygon->Release();
        g_pVtxBuffPolygon = NULL;
    }
    if (g_pTexturePolygon) {
        g_pTexturePolygon->Release();
        g_pTexturePolygon = NULL;
    }
}

// Update polygon position based on input
void UpdatePolygon() {
    //if (GetKeyboardPress(DIK_W)) g_aPolygon.pos.y -= move_Polygon; // Move up
    //if (GetKeyboardPress(DIK_S)) g_aPolygon.pos.y += move_Polygon; // Move down
    //if (GetKeyboardPress(DIK_A)) g_aPolygon.pos.x -= move_Polygon; // Move left
    //if (GetKeyboardPress(DIK_D)) g_aPolygon.pos.x += move_Polygon; // Move right

    //if (GetAsyncKeyState(0x57) & 0x8000) g_aPolygon.pos.y -= move_Polygon; // Move up
    if (GetAsyncKeyState(0x53) & 0x8000) g_aPolygon.pos.y += move_Polygon; // Move down
    if (GetAsyncKeyState(0x41) & 0x8000) g_aPolygon.pos.x -= move_Polygon; // Move left
    if (GetAsyncKeyState(0x44) & 0x8000) g_aPolygon.pos.x += move_Polygon; // Move right

    // Handle jumping
    if (GetAsyncKeyState(0x57) & 0x8000 && !isJumping) { // Space bar for jump
        verticalVelocity = JUMP_VELOCITY;
        isJumping = true;
    }

    // Apply gravity
    verticalVelocity += GRAVITY;
    g_aPolygon.pos.y += verticalVelocity;

    // Check if the polygon has hit the ground
    if (g_aPolygon.pos.y + g_aPolygon.fHeight / 2 > SCREEN_HEIGHT) {
        g_aPolygon.pos.y = SCREEN_HEIGHT - g_aPolygon.fHeight / 2;
        isJumping = false; // Allow jumping again
        verticalVelocity = 0; // Reset vertical velocity
    }

    if ((g_aPolygon.pos.x - g_aPolygon.fWidth / 2) < 0) g_aPolygon.pos.x = g_aPolygon.fWidth / 2;
    if ((g_aPolygon.pos.x + g_aPolygon.fWidth / 2) > SCREEN_WIDTH) g_aPolygon.pos.x = SCREEN_WIDTH - g_aPolygon.fWidth / 2;
    if ((g_aPolygon.pos.y - g_aPolygon.fHeight / 2) < 0) g_aPolygon.pos.y = g_aPolygon.fHeight / 2;
    if ((g_aPolygon.pos.y + g_aPolygon.fHeight / 2) > SCREEN_HEIGHT) g_aPolygon.pos.y = SCREEN_HEIGHT - g_aPolygon.fHeight / 2;

    VERTEX_2D* pVtx;
    g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].pos = D3DXVECTOR3(g_aPolygon.pos.x - sinf(g_fAnglePolygon + g_rotPolygon.z) * g_fLengthPolygon,
        g_aPolygon.pos.y - cosf(g_fAnglePolygon + g_rotPolygon.z) * g_fLengthPolygon, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(g_aPolygon.pos.x + sinf(g_fAnglePolygon - g_rotPolygon.z) * g_fLengthPolygon,
        g_aPolygon.pos.y - cosf(g_fAnglePolygon - g_rotPolygon.z) * g_fLengthPolygon, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(g_aPolygon.pos.x - sinf(g_fAnglePolygon - g_rotPolygon.z) * g_fLengthPolygon,
        g_aPolygon.pos.y + cosf(g_fAnglePolygon - g_rotPolygon.z) * g_fLengthPolygon, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(g_aPolygon.pos.x + sinf(g_fAnglePolygon + g_rotPolygon.z) * g_fLengthPolygon,
        g_aPolygon.pos.y + cosf(g_fAnglePolygon + g_rotPolygon.z) * g_fLengthPolygon, 0.0f);

    pVtx[0].tex.x = g_nPatternAnim_Polygon * (1.0f / maxAnimX_Polygon);
    pVtx[0].tex.y = startAnimY_Polygon;

    pVtx[1].tex.x = (g_nPatternAnim_Polygon * (1.0f / maxAnimX_Polygon)) + (1.0f / maxAnimX_Polygon);
    pVtx[1].tex.y = startAnimY_Polygon;

    pVtx[2].tex.x = g_nPatternAnim_Polygon * (1.0f / maxAnimX_Polygon);
    pVtx[2].tex.y = animRow_Polygon * (1.0f / maxAnimY_Polygon);

    pVtx[3].tex.x = (g_nPatternAnim_Polygon * (1.0f / maxAnimX_Polygon)) + (1.0f / maxAnimX_Polygon);
    pVtx[3].tex.y = animRow_Polygon * (1.0f / maxAnimY_Polygon);

    g_pVtxBuffPolygon->Unlock();
}

// Draw the polygon
void DrawPolygon(LPDIRECT3DDEVICE9 pDevice) {
    pDevice->SetFVF(FVF_VERTEX_2D);
    pDevice->SetTexture(0, g_pTexturePolygon);
    pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

// Get a reference to the polygon
POLYGON* GetPolygon() {
    return &g_aPolygon;
}
