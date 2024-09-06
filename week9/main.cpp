#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include <chrono>
#include "SplashScreen.h"
#include "MainMenu.h"


// Global Direct3D variables
LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;

// Game states
enum GameState {
    SPLASH,
    MAINMENU,
    GAME,
    GAMEOVER
};
GameState gameState = SPLASH;

// Instances for screens
SplashScreen splashScreen;
MainMenu mainMenu;

// Mouse input variables
POINT mousePos;
bool isClick = false;

// Timing for splash screen transition
std::chrono::steady_clock::time_point splashStartTime;
bool splashStarted = false;

int score = 0;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_LBUTTONDOWN:
        isClick = true;
        mousePos.x = LOWORD(lParam);
        mousePos.y = HIWORD(lParam);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void InitD3D(HWND hWnd) {
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;

    d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

    // Initialize screens
    splashScreen.Init(d3ddev, L"Assets\\loading.png");
    mainMenu.Init(d3ddev);
}

void RenderFrame() {
    d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(93, 107, 153), 1.0f, 0);
    d3ddev->BeginScene();

    if (gameState == SPLASH) {
        // Start timing when splash screen starts
        if (!splashStarted) {
            splashStartTime = std::chrono::steady_clock::now();
            splashStarted = true;
        }

        // Render Splash Screen
        splashScreen.Render(d3ddev);

        // Check if 3 seconds have passed or mouse click occurred
        auto elapsedTime = std::chrono::steady_clock::now() - splashStartTime;
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsedTime).count() >= 3 || isClick) {
            gameState = MAINMENU;  // Auto transition to main menu
        }
    }
    else if (gameState == MAINMENU) {
        // Render Main Menu
        mainMenu.Render(d3ddev);

        // Handle input and check button clicks
        mainMenu.HandleInput(mousePos, isClick);

        // Check if buttons are clicked
        if (mainMenu.IsStartClicked()) {
            gameState = GAME;  // Proceed to the game
            if (isClick) {
                gameState = GAME;
            }
        }
        if (mainMenu.IsExitClicked()) {
            PostQuitMessage(0);  // Exit the application
        }
    }
    
    d3ddev->EndScene();
    d3ddev->Present(nullptr, nullptr, nullptr, nullptr);

    isClick = false;  // Reset click state after each frame
}

void Cleanup() {
    splashScreen.Cleanup();
    mainMenu.Cleanup();
    d3ddev->Release();
    d3d->Release();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hWnd;
    WNDCLASSEX wc = {};

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = "WindowClass";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(0, "WindowClass", "Main Menu Example", WS_OVERLAPPEDWINDOW,
        300, 300, 800, 600, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hWnd, nCmdShow);

    InitD3D(hWnd);

    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            RenderFrame();
        }
    }

    Cleanup();
    return msg.wParam;
}
