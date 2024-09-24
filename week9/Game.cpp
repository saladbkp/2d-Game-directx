//#include "Game.h"
//#include <iostream>
//#include "main.cpp"
//
//Game::Game(HWND hwnd)
//    : hWnd(hwnd), b(0, 0, 10), b2(400, 400, 10),
//    o(new Obstacle[num_obstacles]),
//    audioManager(new AudioManager()),
//    settingsManager(new SettingsManager()),
//    roundLost(false),
//    isPaused(false) {
//    // Seed the random number generator
//    rng.seed(rd());
//}
//Game::~Game() {
//    CleanUp();
//}
//
//void Game::Initialize() {
//    CreateDirect3D9(hWnd);
//    CreateFont();
//    InitializeComponents();
//}
//
//void Game::CreateDirect3D9(HWND hWnd) {
//    d3d = Direct3DCreate9(D3D_SDK_VERSION);
//    D3DPRESENT_PARAMETERS d3dpp = {};
//    d3dpp.Windowed = TRUE;
//    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
//    d3dpp.hDeviceWindow = hWnd;
//
//    if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
//        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev))) {
//        MessageBox(NULL, "Failed to create Direct3D device!", "Error", MB_OK);
//        exit(1);
//    }
//}
//
//void Game::CreateFont() {
//    D3DXFONT_DESC fontDesc = {
//        20, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET,
//        OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH,
//        "Arial"
//    };
//
//    if (FAILED(D3DXCreateFontIndirect(d3ddev, &fontDesc, &g_pFont))) {
//        MessageBox(NULL, "Failed to create font!", "Error", MB_OK);
//        return;
//    }
//}
//
//void Game::InitializeComponents() {
//    g_frameTimer.init(60); // 60 FPS
//
//    // Initialize Paddle
//    p.y = gfx.ScreenHeight / 2;
//    p.speed = 3;
//    p.size = 50;
//
//    // Initialize obstacles
//    for (int i = 0; i < num_obstacles; i++) {
//        o[i].x = (i + 1) * 50; // Adjust as needed
//        o[i].y = 10 + rand() % (gfx.ScreenHeight - 100); // Random Y position
//        o[i].vy = -3 + rand() % 7; // Random vertical speed
//        o[i].x_size = 5;
//        o[i].y_size = 80; // Fixed size for now
//    }
//
//    // Initialize Balls
//    b.resetBall(gfx.ScreenWidth - 100, gfx.ScreenHeight / 2, 20);
//    b2.resetBall(b2.x, b2.y);
//
//    // Initialize Leaf and Cactus
//    InitLeaf(d3ddev);
//    leaf = GetLeaf();
//    InitCactus(d3ddev);
//    cactus = GetCactus();
//
//    // Initialize Audio
//    audioManager->InitializeAudio();
//    audioManager->LoadSound();
//    audioManager->PlaySoundTrack(settingsManager);
//
//    // Initialize Settings Menu
//    settingsMenu.Init(d3ddev);
//}
//
//void Game::Update() {
//    // Game update logic
//}
//
//void Game::Render() {
//    // Game rendering logic
//}
//
//void Game::CleanUp() {
//    if (d3ddev) {
//        d3ddev->Release();
//        d3ddev = nullptr;
//    }
//    if (d3d) {
//        d3d->Release();
//        d3d = nullptr;
//    }
//    if (g_pFont) {
//        g_pFont->Release();
//        g_pFont = nullptr;
//    }
//    delete[] o;
//    delete audioManager;
//    delete settingsManager;
//}
