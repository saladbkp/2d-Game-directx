#include "SplashState.h"

void SplashState::Init(LPDIRECT3DDEVICE9 d3ddev) {
    splashScreen.Init(d3ddev, L"Assets\\loading.png");
}

void SplashState::Update(LPDIRECT3DDEVICE9 d3ddev, POINT mousePos, bool isClick, bool isUIClicked, int* score, int* chance, bool* isPaused) {
    if (!splashStarted) {
        splashStartTime = std::chrono::steady_clock::now();
        splashStarted = true;
    }

    auto elapsedTime = std::chrono::steady_clock::now() - splashStartTime;
    if (std::chrono::duration_cast<std::chrono::seconds>(elapsedTime).count() >= 3 || isClick) {
        // Change state (handled in GameStateManager)
        splashStarted = false;
    }
}

void SplashState::Render(LPDIRECT3DDEVICE9 d3ddev) {
    splashScreen.Render(d3ddev);
}

void SplashState::Cleanup() {
    splashScreen.Cleanup();
}
