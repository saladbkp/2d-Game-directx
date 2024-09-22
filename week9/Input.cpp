#include "input.h"
#include <dinput.h>

LPDIRECTINPUT8 g_pInput = NULL;		
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		
BYTE g_keyState[256];
BYTE g_keyStatePress[256];		
BYTE g_keyStateTrigger[256];		
BYTE g_keyStateRelease[256];		

HRESULT InitInput(HINSTANCE hInstance, HWND hwnd)
{
	if (g_pInput == NULL)		
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}





void UninitInput(void)
{
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}





void UpdateInput(void)
{

}





HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))		
	{
		return E_FAIL;
	}
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))		
	{
		return E_FAIL;
	}
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	g_pDevKeyboard->Acquire();		
	return S_OK;
}





void UninitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	UninitInput();
}

void UpadateKeyboard(void)
{
	int cnt;
	BYTE aKeyState[256];


	if (SUCCEEDED(g_pDevKeyboard->
		State(sizeof(aKeyState), &aKeyState[0])))
	{
		for (cnt = 0;cnt < 256;cnt++)
		{

			
			g_keyStateTrigger[cnt] = (g_keyState[cnt] ^ aKeyState[cnt]) & aKeyState[cnt];

			

			g_keyStateRelease[cnt] = (g_keyState[cnt] ^ aKeyState[cnt]) & g_keyState[cnt];
			g_keyState[cnt] = aKeyState[cnt];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}

}

bool GetKeyboardPress(int nKey)
{
	return (g_keyState[nKey] & 0x80) ? true : false;
}


bool GetKeyboardTrigger(int nKey)
{
	return (g_keyStateTrigger[nKey] & 0x80) ? true : false;
}

bool GetKeyboardRelease(int nKey)
{
	return (g_keyStateRelease[nKey] & 0x80) ? true : false;
}





