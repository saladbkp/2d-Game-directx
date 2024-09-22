#pragma once
#include <d3d9.h>

class GameState {
public:
    virtual ~GameState() = default;

    // Initialize the state (e.g., load resources)
    virtual void Init(LPDIRECT3DDEVICE9 d3ddev) = 0;

    // Handle input events
    virtual void HandleInput() = 0;

    // Update game logic
    virtual void Update(float deltaTime) = 0;

    // Render the current state
    virtual void Render() = 0;

    // Handle when the state is exited
    virtual void Exit() = 0;
};
