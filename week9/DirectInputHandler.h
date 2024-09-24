#pragma once
#include <dinput.h>

class DirectInputHandler {
public:
    DirectInputHandler();
    ~DirectInputHandler();

    bool initialize(HINSTANCE hInstance, HWND hWnd);
    void getInput();
    void cleanup();

    bool isKeyPressed(BYTE keyCode);
    LONG getMouseXMovement();
    LONG getMouseYMovement();

private:
    LPDIRECTINPUT8 dInput;
    LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
    LPDIRECTINPUTDEVICE8 dInputMouseDevice;
    BYTE diKeys[256];      // Key input buffer
    DIMOUSESTATE mouseState;  // Mouse state
};

