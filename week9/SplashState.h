#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include "GameState.h"
#include "SplashScreen.h"
#include <chrono>

class SplashState : public GameState {
public:
    void Init(LPDIRECT3DDEVICE9 d3ddev) override;
    void Update(LPDIRECT3DDEVICE9 d3ddev, POINT mousePos, bool isClick, bool isUIClicked, int* score, int* chance, bool* isPaused) override;
    void Render(LPDIRECT3DDEVICE9 d3ddev) override;
    void Cleanup() override;

private:
    SplashScreen splashScreen;
    std::chrono::steady_clock::time_point splashStartTime;
    bool splashStarted = false;
};

#endif // SPLASHSTATE_H
