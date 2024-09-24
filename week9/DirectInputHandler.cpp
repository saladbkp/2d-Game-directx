#include "DirectInputHandler.h"

DirectInputHandler::DirectInputHandler() :
    dInput(NULL),
    dInputKeyboardDevice(NULL),
    dInputMouseDevice(NULL)
{
    ZeroMemory(diKeys, sizeof(diKeys));
    ZeroMemory(&mouseState, sizeof(mouseState));
}

DirectInputHandler::~DirectInputHandler() {
    cleanup();
}

bool DirectInputHandler::initialize(HINSTANCE hInstance, HWND hWnd) {
    // Create DirectInput object
    HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL);
    if (FAILED(hr)) return false;

    // Create keyboard device
    hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
    if (FAILED(hr)) return false;

    dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
    dInputKeyboardDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

    // Create mouse device
    hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
    if (FAILED(hr)) return false;

    dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
    dInputMouseDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

    return true;
}

void DirectInputHandler::getInput() {
    // Get keyboard state
    dInputKeyboardDevice->Acquire();
    dInputKeyboardDevice->GetDeviceState(sizeof(diKeys), (LPVOID)&diKeys);

    // Get mouse state
    dInputMouseDevice->Acquire();
    dInputMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
}

bool DirectInputHandler::isKeyPressed(BYTE keyCode) {
    return (diKeys[keyCode] & 0x80) != 0;
}

LONG DirectInputHandler::getMouseXMovement() {
    return mouseState.lX;
}

LONG DirectInputHandler::getMouseYMovement() {
    return mouseState.lY;
}

void DirectInputHandler::cleanup() {
    if (dInputKeyboardDevice) {
        dInputKeyboardDevice->Unacquire();
        dInputKeyboardDevice->Release();
        dInputKeyboardDevice = NULL;
    }

    if (dInputMouseDevice) {
        dInputMouseDevice->Unacquire();
        dInputMouseDevice->Release();
        dInputMouseDevice = NULL;
    }

    if (dInput) {
        dInput->Release();
        dInput = NULL;
    }
}
