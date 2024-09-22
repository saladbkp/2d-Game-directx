#include "SettingsMenu.h"
#include <d3dx9.h>

// Default constructor
SettingsMenu::SettingsMenu()
	: audioManager(nullptr), settingsManager(nullptr) {
	// Optionally, initialize other members to default values
}
SettingsMenu::SettingsMenu(AudioManager* audioManager, SettingsManager* settingsManager) :
bgRect { 0, 0, 900, 700 }, bgPos(0, 0, 0), closeIconRect{ 0, 0, 64, 64 }, closeIconPos(800, 20, 0),
sliderBarRect{ 0, 0, 400, 32 }, sliderHandleRect{ 0, 0, 64, 64 },
bgmSliderBarPos(350, 325, 0),
bgmSliderHandlePos(bgmSliderBarPos.x + sliderBarRect.right - (sliderHandleRect.right / 2), bgmSliderBarPos.y - (sliderHandleRect.bottom / 4), 0),
sfxSliderBarPos(350, 450, 0),
sfxSliderHandlePos(sfxSliderBarPos.x + sliderBarRect.right - (sliderHandleRect.right / 2), sfxSliderBarPos.y - (sliderHandleRect.bottom / 4), 0),
audioManager(audioManager), settingsManager(settingsManager) {}

void SettingsMenu::Init(LPDIRECT3DDEVICE9 d3ddev)
{
	D3DXCreateTextureFromFile(d3ddev, "Assets\\settingsbg.png", &bgTexture);
	D3DXCreateTextureFromFile(d3ddev, "Assets\\quit-icon.png", &closeIconTexture);
	D3DXCreateTextureFromFile(d3ddev, "Assets\\bar.png", &sliderBarTexture);
	D3DXCreateTextureFromFile(d3ddev, "Assets\\handler.png", &sliderHandleTexture);
}

void SettingsMenu::Render(LPDIRECT3DDEVICE9 d3ddev)
{
	LPD3DXSPRITE sprite;
	D3DXCreateSprite(d3ddev, &sprite);

	// Begin the sprite rendering process
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	// Render the background image
	sprite->Draw(bgTexture, &bgRect, nullptr, &bgPos, D3DCOLOR_XRGB(255, 255, 255));

	// Render the close icon
	sprite->Draw(closeIconTexture, &closeIconRect, nullptr, &closeIconPos, D3DCOLOR_XRGB(255, 255, 255));

	// Render the slider bar and slider handle
	sprite->Draw(sliderBarTexture, &sliderBarRect, nullptr, &bgmSliderBarPos, D3DCOLOR_XRGB(255, 255, 255));
	sprite->Draw(sliderHandleTexture, &sliderHandleRect, nullptr, &bgmSliderHandlePos, D3DCOLOR_XRGB(255, 255, 255));
	sprite->Draw(sliderBarTexture, &sliderBarRect, nullptr, &sfxSliderBarPos, D3DCOLOR_XRGB(255, 255, 255));
	sprite->Draw(sliderHandleTexture, &sliderHandleRect, nullptr, &sfxSliderHandlePos, D3DCOLOR_XRGB(255, 255, 255));

	// End the sprite rendering process
	sprite->End();

	sprite->Release();
}

void SettingsMenu::HandleInput(POINT mousePos, bool isClick)
{
	if (isClick) {
		if (mousePos.x >= closeIconPos.x && mousePos.x <= closeIconPos.x + closeIconRect.right &&
			mousePos.y >= closeIconPos.y && mousePos.y <= closeIconPos.y + closeIconRect.bottom) {
			closeClicked = true;
		}

		// Check if the bgm slider bar/handle is clicked
		if (mousePos.x >= bgmSliderBarPos.x && mousePos.x <= bgmSliderBarPos.x + sliderBarRect.right &&
			mousePos.y >= bgmSliderBarPos.y && mousePos.y <= bgmSliderBarPos.y + sliderBarRect.bottom ||
			mousePos.x >= bgmSliderHandlePos.x && mousePos.x <= bgmSliderHandlePos.x + (sliderHandleRect.right - sliderHandleRect.left) &&
			mousePos.y >= bgmSliderHandlePos.y && mousePos.y <= bgmSliderHandlePos.y + (sliderHandleRect.bottom - sliderHandleRect.top)) {
			AdjustBgmVolume(mousePos);
		}

		// Check if the sfx slider bar/handle is clicked
		if (mousePos.x >= sfxSliderBarPos.x && mousePos.x <= sfxSliderBarPos.x + sliderBarRect.right &&
			mousePos.y >= sfxSliderBarPos.y && mousePos.y <= sfxSliderBarPos.y + sliderBarRect.bottom ||
			mousePos.x >= sfxSliderHandlePos.x && mousePos.x <= sfxSliderHandlePos.x + (sliderHandleRect.right - sliderHandleRect.left) &&
			mousePos.y >= sfxSliderHandlePos.y && mousePos.y <= sfxSliderHandlePos.y + (sliderHandleRect.bottom - sliderHandleRect.top)) {
			AdjustSfxVolume(mousePos);
		}
	}
}

void SettingsMenu::AdjustBgmVolume(POINT mousePos)
{
	float bgmSliderBarStartX = bgmSliderBarPos.x;
	float bgmSliderBarEndX = bgmSliderBarPos.x + sliderBarRect.right;

	bgmSliderHandlePos.x = max(bgmSliderBarStartX - (sliderHandleRect.right / 2), min(mousePos.x - (sliderHandleRect.right / 2), bgmSliderBarEndX - (sliderHandleRect.right / 2)));

	float volume = (bgmSliderHandlePos.x + (sliderHandleRect.right / 2) - bgmSliderBarStartX) / (bgmSliderBarEndX - bgmSliderBarStartX);
	bgmVolume = (volume < 0) ? 0 : (volume > 1) ? 1 : volume; // Clamp between 0 and 1
	settingsManager->SetBGMVolume(bgmVolume);
	audioManager->UpdateVolume(settingsManager);
	volumeAdjusted = true;
}

void SettingsMenu::AdjustSfxVolume(POINT mousePos)
{
	float sfxSliderBarStartX = sfxSliderBarPos.x;
	float sfxSliderBarEndX = sfxSliderBarPos.x + sliderBarRect.right;

	sfxSliderHandlePos.x = max(sfxSliderBarStartX - (sliderHandleRect.right / 2), min(mousePos.x - (sliderHandleRect.right / 2), sfxSliderBarEndX - (sliderHandleRect.right / 2)));

	float volume = (sfxSliderHandlePos.x + (sliderHandleRect.right / 2) - sfxSliderBarStartX) / (sfxSliderBarEndX - sfxSliderBarStartX);
	sfxVolume = (volume < 0) ? 0 : (volume > 1) ? 1 : volume; // Clamp between 0 and 1
	settingsManager->SetSFXVolume(sfxVolume);
	audioManager->UpdateVolume(settingsManager);
	volumeAdjusted = true;
}

bool SettingsMenu::IsVolumeAdjusted()
{
	return volumeAdjusted;
}

bool SettingsMenu::IsCloseClicked()
{
	return closeClicked;
}

void SettingsMenu::Reset()
{
	volumeAdjusted = false;
	closeClicked = false;
}

void SettingsMenu::Cleanup()
{
	// Release textures
	if (bgTexture) {
		bgTexture->Release();
		bgTexture = nullptr;
	}
	if (closeIconTexture) {
		closeIconTexture->Release();
		closeIconTexture = nullptr;
	}
	if (sliderBarTexture) {
		sliderBarTexture->Release();
		sliderBarTexture = nullptr;
	}
	if (sliderHandleTexture) {
		sliderHandleTexture->Release();
		sliderHandleTexture = nullptr;
	}
}
