#include "GameStateManager.h"
#include <chrono>

// Constructor without parameters
GameStateManager::GameStateManager()
    : currentState(SPLASH) {}  // Start with the splash screen state

// Initialize all screens
void GameStateManager::Init(LPDIRECT3DDEVICE9 d3ddev) {
    // Initialize screens with required devices and resources
    splashScreen.Init(d3ddev, L"Assets\\loading.png");
    gameOverScreen.Init(d3ddev, L"Assets\\gameover.png");
    mainMenu.Init(d3ddev);
    scollingBg.Init(d3ddev, ".\\Assets\\bgBamboo_01.png", ".\\Assets\\bgBamboo_02.png", ".\\Assets\\bgBamboo_03.png", 800, 600);
    pauseScreen.Init(d3ddev);
}

// Update method based on current game state
void GameStateManager::Update(LPDIRECT3DDEVICE9 d3ddev, POINT mousePos, bool isClick, bool isUIClicked, int* score, int* chance, bool* isPaused) {
    static bool splashStarted = false;
    static std::chrono::steady_clock::time_point splashStartTime;



    switch (currentState) {
    case SPLASH: {
        // Start timing when splash screen starts
        if (!splashStarted) {
            splashStartTime = std::chrono::steady_clock::now();
            splashStarted = true;
        }

        // Render the Splash Screen
        //splashScreen.Render(d3ddev);

        // Check if 3 seconds have passed or mouse click occurred
        auto elapsedTime = std::chrono::steady_clock::now() - splashStartTime;
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsedTime).count() >= 3 || isClick) {
            currentState = MAINMENU;  // Auto transition to main menu
            splashStarted = false;    // Reset splash flag for future splash screen usage
        }
        break;
    }

    case MAINMENU: {
        // Render Main Menu
        //mainMenu.Render(d3ddev);

        // Handle input and check button clicks
        mainMenu.HandleInput(mousePos, isClick);

        // Check if buttons are clicked
        if (mainMenu.IsStartClicked()) {
            currentState = GAME;  // Proceed to the game
            isUIClicked = true;
        }
        else if (mainMenu.IsSettingsClicked()) {
            currentState = SETTINGS;
            isUIClicked = true;
        }
        else if (mainMenu.IsExitClicked()) {
            //PostQuitMessage(0);  // Exit the application
        }
        break;
    }

    case GAME: {
        if (*chance == 0) {
            *isPaused = false;
            currentState = GAMEOVER;
        }
        if (*isPaused) {
            currentState = PAUSE;
        }
        else {
            //// Update the background and player movement based on input
            HandlePlayerMovement(&scollingBg);  // Example of a player movement function
        }
        break;
    }
    case PAUSE: {
        // Check if the user presses the space key to resume the game
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            *isPaused = false;  // Exit pause mode
            currentState = GAME;
        }
        break;
    }
    case GAMEOVER: {
        // Render the Game Over screen
        //gameOverScreen.Render(d3ddev);

        // Handle input to restart or go back to the main menu
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            currentState = GAME;  // Restart the game
        }
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            currentState = MAINMENU;  // Go back to the main menu
        }
        *isPaused = false;
        *score = 0;  // Reset score
        *chance = 3;  // Reset chance
        break;
    }
    }
}

int GameStateManager::GetCurrentState() const {
    return currentState;  // Return the value of the currentState member
}

void GameStateManager::SetCurrentState(int state) {
    currentState = state;  // Return the value of the currentState member
}

// Render method based on current game state
void GameStateManager::Render(LPDIRECT3DDEVICE9 d3ddev) {
    switch (currentState) {
    case SPLASH:
        splashScreen.Render(d3ddev);
        break;
    case MAINMENU:
        mainMenu.Render(d3ddev);
        break;
    case GAME:
        //// Render the scrolling background
        scollingBg.Render(d3ddev);
        break;
    case PAUSE:
        pauseScreen.Render(d3ddev);
        break;
    case GAMEOVER:
        gameOverScreen.Render(d3ddev);
        break;
    }
}

void GameStateManager::CleanUp() {
    splashScreen.Cleanup();
    mainMenu.Cleanup();
    scollingBg.Cleanup();
    pauseScreen.Cleanup();
    gameOverScreen.Cleanup();

}