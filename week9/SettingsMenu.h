#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "audioManager.h"
#include "settingsManager.h"

class SettingsMenu {
private:
	LPDIRECT3DTEXTURE9 bgTexture;
	RECT bgRect;
	D3DXVECTOR3 bgPos;

	LPDIRECT3DTEXTURE9 closeIconTexture;
	RECT closeIconRect;
	D3DXVECTOR3 closeIconPos;

	LPDIRECT3DTEXTURE9 sliderBarTexture;
	LPDIRECT3DTEXTURE9 sliderHandleTexture;
	RECT sliderBarRect;
	RECT sliderHandleRect;
	D3DXVECTOR3 bgmSliderBarPos;
	D3DXVECTOR3 bgmSliderHandlePos;
	D3DXVECTOR3 sfxSliderBarPos;
	D3DXVECTOR3 sfxSliderHandlePos;

	bool settingsClicked;
	bool volumeAdjusted;
	bool closeClicked;

	AudioManager* audioManager;
	SettingsManager* settingsManager;
	float bgmVolume;
	float sfxVolume;

public:
	// Default constructor
	SettingsMenu();
	SettingsMenu(AudioManager* audioManager, SettingsManager* settingsManager);
	void Init(LPDIRECT3DDEVICE9 d3ddev);
	void Render(LPDIRECT3DDEVICE9 d3ddev);
	void HandleInput(POINT mousePos, bool isClick);
	void AdjustBgmVolume(POINT mousePos);
	void AdjustSfxVolume(POINT mousePos);
	bool IsVolumeAdjusted();
	bool IsCloseClicked();
	void Reset();
	void Cleanup();
};

#endif