#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include <chrono>
#include "SplashScreen.h"
#include "MainMenu.h"
#include "CustomShapes.h"
#include "Ball.h"
#include <cstdlib>
#include "Obstacle.h"
#include <random>
#include "Paddle.h"
#include "Polygon.h"
#include <dinput.h>
#include "Input.h"
#include "FrameTimer.h"
#include <string>


// Global Direct3D variables
LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;

// fps
// Global variables
LPD3DXFONT g_pFont = nullptr;
FrameTimer g_frameTimer;

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
SplashScreen gameOverScreen;
MainMenu mainMenu;

// Mouse input variables
POINT mousePos;
bool isClick = false;

// Timing for splash screen transition
std::chrono::steady_clock::time_point splashStartTime;
bool splashStarted = false;

Graphics gfx;  // Graphics object to use in CustomShapes

// setup components
Ball b;
Ball b2(400, 400, 10);
const int num_obstacles = 8;
Obstacle* o = new Obstacle[num_obstacles];
int maxObjectHeight = 100;
int obstacle_x_spacing = 50;
int obstacle_x_size = 5;
int obstacle_y_size = 80;
Paddle p;

// SETUP POLYGON
POLYGON* player;

std::random_device rd;
std::mt19937 rng(rd());

const float GRAVITY = 9.8f; // Acceleration due to gravity
const float ACCELERATION = 0.2f; // Acceleration when moving
const float DECELERATION = 0.1f; // Deceleration due to friction
const float MAX_SPEED = 5.0f; // Maximum speed of the ball

// Define constants for normal speed and speed increment
const float NORMAL_SPEED_X = 5.0f; // Normal speed along x-axis
const float NORMAL_SPEED_Y = 2.5f; // Normal speed along y-axis
const float SPEED_INCREMENT = 0.5f; // Speed increase on collision

// score font
int score = 0;
int highscore = 0;
int chance = 3;
LPD3DXFONT g_pFontScore = nullptr;


// helper function
// Custom max function
template<typename T>
T Max(T a, T b) {
    return (a > b) ? a : b;
}

// Custom min function
template<typename T>
T Min(T a, T b) {
    return (a < b) ? a : b;
}

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

    // init fps
    D3DXFONT_DESC fontDesc = {
        20, // Height
        0,  // Width
        FW_NORMAL, // Weight
        1, // MipLevels
        false, // Italic
        DEFAULT_CHARSET, // CharSet
        OUT_DEFAULT_PRECIS, // Precision
        ANTIALIASED_QUALITY, // Quality
        DEFAULT_PITCH, // PitchAndFamily
        "Arial" // FontFamily
    };

    D3DXFONT_DESC fontScoreDesc = {
        24, // Height
        0,  // Width
        FW_NORMAL, // Weight
        1, // MipLevels
        false, // Italic
        DEFAULT_CHARSET, // CharSet
        OUT_DEFAULT_PRECIS, // Precision
        ANTIALIASED_QUALITY, // Quality
        DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
        "Segoe UI Emoji" // FontFamily
    };
    if (FAILED(D3DXCreateFontIndirect(d3ddev, &fontDesc, &g_pFont)))
    {
        MessageBox(NULL, "Failed to create font!", "Error", MB_OK);
        return;
    }
    if (FAILED(D3DXCreateFontIndirect(d3ddev, &fontScoreDesc, &g_pFontScore)))
    {
        MessageBox(NULL, "Failed to create heart font!", "Error", MB_OK);
        return;
    }

    g_frameTimer.init(6000); // 60 FPS

    // Initialize screens
    splashScreen.Init(d3ddev, L"Assets\\loading.png");
    gameOverScreen.Init(d3ddev, L"Assets\\result.png");
    mainMenu.Init(d3ddev);

    // Init Components
    // 
    p.y = gfx.ScreenHeight / 2;
    p.speed = 3;
    p.size = 50;
    // 
    // Code used to set the randomise seeds
    std::uniform_int_distribution<int> _y(10, gfx.ScreenHeight - 10 - maxObjectHeight);
    std::uniform_int_distribution<int> _vy(-3, 3);
    std::uniform_int_distribution<int> _ysize(30, maxObjectHeight - 30);

    for (int i = 0; i < num_obstacles; i++)
    {
        o[i].x = (i + 1) * obstacle_x_spacing;
        o[i].y = _y(rng);
        o[i].vy = _vy(rng);
        while (o[i].vy == 0)
        {
            o[i].vy = _vy(rng);
        }
        o[i].x_size = obstacle_x_size;
        o[i].y_size = _ysize(rng);

    }
    b.resetBall(gfx.ScreenWidth - 100, gfx.ScreenHeight / 2, 20);
    b2.resetBall(b2.x, b2.y);

    // Initialize the polygon here
    InitPolygon(d3ddev);
    player = GetPolygon();  // Fetch polygon instance if needed
}

// render fps
// Render FPS on the screen
void RenderFPS()
{
    if (!g_pFont)
    {
        // If g_pFont is not initialized, return immediately
        return;
    }

    char fpsText[256];
    int framesToUpdate = g_frameTimer.framesToUpdate();
    float fps = 0.0f;

    if (framesToUpdate > 0)
    {
        fps = (float)framesToUpdate / g_frameTimer.deltaTime * 1000.0f;
    }

    sprintf_s(fpsText, "FPS: %.4f", fps);

    //// Begin scene
    //d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    //d3ddev->BeginScene();

    RECT textRect = { 10, 10, 0, 0 };
    g_pFont->DrawText(NULL, fpsText, -1, &textRect, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

    //// End scene
    //d3ddev->EndScene();
    //d3ddev->Present(NULL, NULL, NULL, NULL);
}

// reder font
void RenderScore() {
    if (g_pFont) {
        // Convert score to a string
        char roundText[256];
        char scoreText[256];
        char highscoreText[256];
        sprintf_s(roundText, "ROUND: %d", chance);
        sprintf_s(scoreText, "Score: %d", score);
        sprintf_s(highscoreText, "Highest Score: %d", highscore);
        // Set the position and rectangle for the text
        //RECT textRect;
        //SetRect(&textRect, 800 - 100, 700 - 30, 800, 700); // Example position
        RECT roundRect = { 600, 50, 800, 600 };
        RECT textRect = { 600, 500, 800, 600 };
        RECT textRect2 = { 600, 550, 800, 600 };
        // Draw the text
        g_pFont->DrawText(NULL, roundText, -1, &roundRect, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
        g_pFont->DrawText(NULL, scoreText, -1, &textRect, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
        g_pFont->DrawText(NULL, highscoreText, -1, &textRect2, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
    }
    if (g_pFontScore) {
        // Define the text with the ❤️ emoji
        char scoreText[256];
        const char* heartText = "";

        // Define the rectangle where the text will be rendered
        RECT textRect = { 800, 10, 1000, 50 }; // Adjust as needed

        // Set the font color (white in this case)
        D3DCOLOR textColor = D3DCOLOR_XRGB(255, 255, 255);

        // Render the text including the emoji
        g_pFont->DrawText(
            NULL,                        // No specific render target
            heartText,                   // The text to render
            -1,                          // -1 to indicate the text is null-terminated
            &textRect,                   // Rectangle defining the text area
            DT_LEFT | DT_NOCLIP,         // Text alignment and clipping options
            textColor                    // Text color
        );
    }

}


// obstacle hit
bool obstacleHitx(int i)
{

    if (b.vx > 0)
    {
        return (b.x >= (o[i].x) - (b.diameter / 2) &&
            b.x <= o[i].x - (b.diameter / 2) + b.vx &&
            b.y - b.diameter / 2 <= o[i].y + o[i].y_size &&
            b.y + b.diameter / 2 >= o[i].y);
    }
    else if (b.vx < 0)
    {
        return (b.x - b.diameter / 2 <= (o[i].x) + o[i].x_size &&
            b.x - b.diameter / 2 >= o[i].x + o[i].x_size + b.vx &&
            b.y - b.diameter / 2 <= o[i].y + o[i].y_size &&
            b.y + b.diameter / 2 >= o[i].y);
    }
    else
    {
        return false;
    }
}

bool obstacleHity(int i)
{

    if (b.vy > 0)
    {
        return (b.y + b.diameter / 2 >= o[i].y &&
            b.y + b.diameter / 2 <= o[i].y + b.vy &&
            b.x + b.diameter / 2 >= o[i].x &&
            b.x - b.diameter / 2 <= o[i].x + o[i].x_size
            );
    }
    else if (b.vy < 0)
    {
        return (b.y - b.diameter / 2 <= o[i].y + o[i].y_size &&
            b.y - b.diameter / 2 >= o[i].y + o[i].y_size + b.vy &&
            b.x + b.diameter / 2 >= o[i].x &&
            b.x - b.diameter / 2 <= o[i].x + o[i].x_size
            );
    }
    else
    {
        return false;
    }
}

bool paddleHit()
{
    return (b.vx > 0 &&
        b.x > (p.x) - (b.diameter / 2) &&
        b.x + b.diameter / 2 > p.x + 3 &&
        b.y - b.diameter / 2 < p.y + p.size / 2 &&
        b.y + b.diameter / 2 > p.y - p.size / 2);
}

void UpdateModel() {
    if (GetAsyncKeyState(VK_UP) & 0x8000) {

        p.y -= p.speed;
    }

    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {

        p.y += p.speed;
    }
    
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        
        if (!b.inMotion)
        {
            b.vx = -NORMAL_SPEED_X;
            b.vy = NORMAL_SPEED_Y;
            b.inMotion = true;
        }
    }

    // Apply gravity to ball
    //b.vy += GRAVITY * g_frameTimer.deltaTime;

    if (b.y > (gfx.ScreenHeight - 10) - (b.diameter / 2) - abs(b.vy))
    {
        b.vy = -b.vy;
    }

    if (b.y < 10 + (b.diameter / 2) + abs(b.vy))
    {
        b.vy = -b.vy;
    }

    if (b.x > (gfx.ScreenWidth - 10) - (b.diameter / 2) - abs(b.vx))
    {
        b.vx = -NORMAL_SPEED_X; // Reset to normal speed
        b.vy = NORMAL_SPEED_Y; // Reset to normal speed
        b.resetBall(gfx.ScreenWidth - 100, gfx.ScreenHeight / 2);
        score = 0;
        chance -= 1;
        if (chance == 0) {
            gameState = GAMEOVER;
        }
        
    }

    if (b.x < 10 + (b.diameter / 2) + abs(b.vx))
    {
        b.vx = -b.vx;
    }

    // for paddles
    if (p.y < 10 + (p.size / 2))
    {
        p.y = 10 + (p.size / 2);
    }

    if (p.y > gfx.ScreenHeight - 10 - (p.size / 2))
    {
        p.y = gfx.ScreenHeight - 10 - (p.size / 2);
    }

    // for obstacles
    for (int i = 0; i < num_obstacles; i++)
    {
        if (o[i].y > gfx.ScreenHeight - 10 - o[i].y_size)
        {
            o[i].vy = -o[i].vy;
        }

        if (o[i].y < 10)
        {
            o[i].vy = -o[i].vy;
        }
    }

    for (int i = 0; i < num_obstacles; i++) {
        if (obstacleHitx(i) || obstacleHity(i)) {
            b.vx = -b.vx; // Reflect velocity on x-axis
            b.vy = -b.vy; // Reflect velocity on y-axis

            // Increase speed on collision
            b.vx += (b.vx > 0) ? SPEED_INCREMENT : -SPEED_INCREMENT;
            b.vy += (b.vy > 0) ? SPEED_INCREMENT : -SPEED_INCREMENT;
        }
    }

    // Check for collision with paddle
    if (paddleHit()) {
        score += 10;
        if (score > highscore) {
            highscore = score;
        }
        b.vx = -b.vx; // Reflect velocity on x-axis

        // Increase speed on collision
        b.vx += (b.vx > 0) ? SPEED_INCREMENT : -SPEED_INCREMENT;
        b.vy += (b.vy > 0) ? SPEED_INCREMENT : -SPEED_INCREMENT;
        //// Apply deceleration to simulate friction
        //b.vx = Max(-MAX_SPEED, Min(MAX_SPEED, b.vx)); // Clamp speed
        //b.vy = Max(-MAX_SPEED, Min(MAX_SPEED, b.vy)); // Clamp speed

        if (p.size > 20) {
            p.size -= 1;
        }
        if (b.diameter > 10) {
            b.diameter -= 1;
        }
    }
    
    b.x += b.vx;
    b.y += b.vy;

    

    for (int i = 0; i < num_obstacles; i++)
    {
        o[i].y += o[i].vy;
    }

    // Update polygon state in the game loop
    UpdatePolygon();
}

void ComposeFrame() {
    CustomShapes::drawCourt(gfx);
    b.drawCircle(gfx, b.x, b.y, b.diameter / 2, 0, 0, 200);
    p.drawPaddle(gfx, p.y, p.size);
    for (int i = 0; i < num_obstacles; i++)
    {
        o[i].drawObstacle(gfx, o[i].x, o[i].y);
    }

    // Draw the polygon during frame composition
    DrawPolygon(d3ddev);
}

void RenderFrame() {
    d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(93, 107, 153), 1.0f, 0);
    d3ddev->BeginScene();

    // render here
    RenderFPS();
    RenderScore();

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
    else if (gameState == GAME) {
        UpdateModel();
        ComposeFrame();
    }
    else if (gameState == GAMEOVER) {
        gameOverScreen.Render(d3ddev);
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
    g_pFont->Release();
    g_pFontScore->Release();
    UninitPolygon();
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
        300, 300, 900, 700, nullptr, nullptr, hInstance, nullptr);

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

LPDIRECT3DDEVICE9 GetDevice(void)
{
    return d3ddev;
}

