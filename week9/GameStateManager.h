#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "SplashScreen.h"
#include "MainMenu.h"
#include "SettingsMenu.h"
#include "background.h"
#include <d3d9.h>
#include "PauseScreen.h"

class GameStateManager {
public:
    // Game states defined as integers
    static const int SPLASH = 1;
    static const int MAINMENU = 2;
    static const int GAME = 3;
    static const int PAUSE = 4;
    static const int GAMEOVER = 5;
    static const int SETTINGS = 6;
    // Constructor
    GameStateManager();

    // Initialize all screens
    void Init(LPDIRECT3DDEVICE9 d3ddev);

    // Update based on current state
    void Update(LPDIRECT3DDEVICE9 d3ddev, POINT mousePos, bool isClick, bool isUIClicked,int* score, int* chance, bool* isPaused);

    // Render based on current state
    void Render(LPDIRECT3DDEVICE9 d3ddev);
    int GetCurrentState() const;
    void SetCurrentState(int state);
    void CleanUp();

private:
    int currentState;  // Current state of the game
    SplashScreen splashScreen;
    SplashScreen gameOverScreen;
    MainMenu mainMenu;
    ScrollingBackground scollingBg;  // Background pointer
    PauseScreen pauseScreen;
};

#endif // GAMESTATEMANAGER_H
