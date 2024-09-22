#include "GameStateManager.h"
#include <chrono>

// Constructor without parameters
GameStateManager::GameStateManager()
    : currentState(SPLASH) {}  // Start with the splash screen state

// Initialize all screens
void GameStateManager::Init(LPDIRECT3DDEVICE9 d3ddev, AudioManager* audioManager, SettingsManager* settingsManager) {
    // Initialize screens with required devices and resources
    splashScreen.Init(d3ddev, L"Assets\\loading.png");
    gameOverScreen.Init(d3ddev, L"Assets\\gameover.png");
    mainMenu.Init(d3ddev);
    settingsMenu = SettingsMenu(audioManager, settingsManager);  // Set up SettingsMenu with managers
    settingsMenu.Init(d3ddev);
}

// Update method based on current game state
void GameStateManager::Update(LPDIRECT3DDEVICE9 d3ddev, POINT mousePos, bool isClick, bool isUIClicked, int* score, int* chance, ScrollingBackground* bg, bool* isPaused, LPD3DXSPRITE spritepauseHandler, LPDIRECT3DTEXTURE9 pauseTexture) {
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
        splashScreen.Render(d3ddev);

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
        mainMenu.Render(d3ddev);

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
            PostQuitMessage(0);  // Exit the application
        }
        break;
    }

    case SETTINGS: {
        // Render the Settings Menu
        settingsMenu.Render(d3ddev);

        // Handle input for sliders and close button
        settingsMenu.HandleInput(mousePos, isClick);

        // If volume adjusted or settings closed, transition back to the main menu
        if (settingsMenu.IsVolumeAdjusted()) {
            settingsMenu.Reset();
            isUIClicked = true;
        }
        if (settingsMenu.IsCloseClicked()) {
            currentState = MAINMENU;  // Go back to the main menu
            settingsMenu.Reset();
            isUIClicked = true;
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
            HandlePlayerMovement(*bg);  // Example of a player movement function

            //// Render the scrolling background
            bg->Render(d3ddev);
        }
       
        break;
    }
    case PAUSE: {
        // Render pause screen
        d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

        // Begin the scene
        d3ddev->BeginScene();

        // Begin the sprite drawing process
        spritepauseHandler->Begin(D3DXSPRITE_ALPHABLEND);

        // Get texture details for the pause image
        D3DSURFACE_DESC desc;
        pauseTexture->GetLevelDesc(0, &desc);
        int imageWidth = desc.Width;
        int imageHeight = desc.Height;

        // Set position to draw the pause texture (center it on screen)
        D3DXVECTOR3 position(0, 0, 0);

        // Draw the pause texture
        spritepauseHandler->Draw(pauseTexture, NULL, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));

        // End the sprite drawing
        spritepauseHandler->End();

        // End the scene
        d3ddev->EndScene();

        // Present the back buffer to the display
        d3ddev->Present(NULL, NULL, NULL, NULL);

        // Check if the user presses the space key to resume the game
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            *isPaused = false;  // Exit pause mode
            currentState = GAME;
        }
        break;
    }
    case GAMEOVER: {
        // Render the Game Over screen
        gameOverScreen.Render(d3ddev);

        // Handle input to restart or go back to the main menu
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            currentState = GAME;  // Restart the game
            *score = 0;  // Reset score
            *chance = 3;  // Reset chance
        }
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            currentState = MAINMENU;  // Go back to the main menu
        }
        break;
    }
    }
}

int GameStateManager::GetCurrentState() const {
    return currentState;  // Return the value of the currentState member
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
    case GAMEOVER:
        gameOverScreen.Render(d3ddev);
        break;
    case SETTINGS:
        settingsMenu.Render(d3ddev);
        break;
    }
}
