//#ifndef GAME_H
//#define GAME_H
//
//#include <d3d9.h>
//#include <d3dx9.h>
//#include <windows.h>
//#include <chrono>
//#include "Ball.h"
//#include "Obstacle.h"
//#include "Paddle.h"
//#include "Polygon.h"
//#include "Cactus.h"
//#include "Leaf.h"
//#include "AudioManager.h"
//#include "SettingsManager.h"
//#include "SettingsMenu.h"
//#include "FrameTimer.h"
//#include "DirectInputHandler.h"
//#include <random>
//
//class Game {
//public:
//    Game(HWND hwnd);
//    ~Game();
//
//    void Initialize();
//    void Update();
//    void Render();
//    void CleanUp();
//
//private:
//    void CreateDirect3D9(HWND hWnd);
//    void CreateFont();
//    void CreateLine();
//    void InitializeComponents();
//
//    HWND hWnd;
//    LPDIRECT3D9 d3d;
//    LPDIRECT3DDEVICE9 d3ddev;
//
//    LPD3DXFONT g_pFont;
//    FrameTimer g_frameTimer;
//
//    Ball b;
//    Ball b2;
//    LEAF* leaf;
//    const int num_obstacles = 8;
//    Obstacle* o;
//    Paddle p;
//    POLYGON* player;
//    CACTUS* cactus;
//
//    AudioManager* audioManager;
//    SettingsManager* settingsManager;
//    SettingsMenu settingsMenu;
//
//    std::random_device rd;
//    std::mt19937 rng;
//
//    bool roundLost;
//    bool isPaused;
//};
//
//#endif // GAME_H
