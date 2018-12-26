/* This file is part of T-Rekt NX!

Copyright (C) 2018/2019 Manuel Rodríguez Matesanz
>    This program is free software: you can redistribute it and/or modify
>    it under the terms of the GNU General Public License as published by
>    the Free Software Foundation, either version 3 of the License, or
>    (at your option) any later version.
>
>    This program is distributed in the hope that it will be useful,
>    but WITHOUT ANY WARRANTY; without even the implied warranty of
>    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
>    GNU General Public License for more details.
>
>    You should have received a copy of the GNU General Public License
>    along with this program.  If not, see <http://www.gnu.org/licenses/>.
>    See LICENSE for information.
*/


#include "TitleScreen.hpp"
#include "SceneManager.hpp"
#include "Filepaths.h"
#include "Colors.h"

TitleScreen::TitleScreen(Settings * settings) : Scene(settings)
{
	this->m_changeScene = false;
	this->m_showingSettings = false;
}

TitleScreen::~TitleScreen()
{
	this->m_music->End(this->m_helper);
	delete(this->m_music);

	this->m_buttonTapSFX->End(this->m_helper);
	delete(this->m_buttonTapSFX);

	this->m_playButton->End(this->m_helper);
	delete(this-> m_playButton);	
	
	this->m_settingsButton->End(this->m_helper);
	delete(this->m_settingsButton);

	this->m_background->End(this->m_helper);
	delete(this->m_background);

	this->m_logo->End(this->m_helper);
	delete(this->m_logo);

	this->m_creatorText->End(this->m_helper);
	delete(this->m_creatorText);

	this->m_muteToggle->End(this->m_helper);
	delete(this->m_muteToggle);	
	
	this->m_backButton->End(this->m_helper);
	delete(this->m_backButton);
}

void TitleScreen::Start(SDL_Helper * helper)
{

	this->m_helper = helper;
	this->m_background = new Sprite(0, 0, helper, IMG_BACKGROUND_TITLE, 1, 1, SWITCH_SCREEN_WIDTH, SWITCH_SCREEN_HEIGHT, 0, 0, false, false);
	this->m_logo = new Sprite(300, 90, helper, IMG_LOGO, 1, 1, 658, 160, 0, 0, false, false);

	this->m_creatorText = new Text(helper, "Manurocker95 (C) 2018", 1000, 650, 15, true, FONT_NORMAL, WHITE);

	this->m_playButton = new Button(500, 310, this->m_helper, IMG_BTN_PLAY, IMG_BTN_PLAY_NON_INTERACTABLE, IMG_BTN_PLAY_PRESSED, true, false, 1, 1, 266, 110, false, 0, 0);
	this->m_settingsButton = new Button(390, 450, this->m_helper, IMG_BTN_SETTINGS, IMG_BTN_SETTINGS_NON_INTERACTABLE, IMG_BTN_SETTINGS_PRESSED, true, false, 1, 1, 508, 110, false, 0, 0);
	this->m_backButton = new Button(60, 560, this->m_helper, IMG_BTN_BACK, IMG_BTN_BACK_NON_INTERACTABLE, IMG_BTN_BACK_PRESSED, true, false, 1, 1, 100, 100, false, 0, 0);

	this->m_muteToggle = new Toggle(350, 380, this->m_helper, IMG_TOGGLE_MUTE_ON, IMG_TOGGLE_MUTE_OFF, true, false, 1, 1, 516, 112, false, 0, 0);

	this->m_buttonTapSFX = new SfxSound(this->m_helper, SND_SFX_TAP, false, 2);
	this->m_music = new MusicSound(this->m_helper, SND_BGM_TITLE, true, 1);
	this->m_music->Play(this->m_helper);


	if (this->m_muted)
		this->m_helper->SDL_PauseMusic();
	
}

void TitleScreen::Draw()
{
	// Sprites
	this->m_background->Draw(this->m_helper);
	this->m_logo->Draw(this->m_helper);

	if (!this->m_showingSettings)
	{
		// Draw Buttons
		this->m_playButton->Draw(this->m_helper);
		this->m_settingsButton->Draw(this->m_helper);
	}
	else
	{
		this->m_muteToggle->Draw(this->m_helper);
		this->m_backButton->Draw(this->m_helper);
	}
	
	// Creator text
	this->m_creatorText->Draw(this->m_helper);
}

void TitleScreen::Update()
{
	if (this->m_changeScene)
		NextScene();
}

void TitleScreen::CheckInputs(u64 kDown, u64 kHeld, u64 kUp)
{
	if (!this->m_showingSettings)
	{

		if (kHeld & KEY_TOUCH)
		{
			u32 j;
			hidTouchRead(&touch, j);

			if (this->m_playButton->IsPressed(&touch))
			{
				//
			}

			if (this->m_settingsButton->IsPressed(&touch))
			{
				//
			}

		}
		else if (kUp & KEY_TOUCH)
		{
			if (this->m_playButton->GetPressed())
			{
				this->m_changeScene = true;

				if (this->m_muted)
					this->m_buttonTapSFX->Play(this->m_helper);

				return;
			}

			if (this->m_settingsButton->GetPressed())
			{
				this->m_showingSettings = true;
				this->m_settingsButton->SetPressed(false);
				return;
			}
		}

		if (kDown & KEY_Y)
		{
			this->m_showingSettings = true;
			return;
		}

		if (kDown & KEY_A)
		{
			this->m_changeScene = true;

			if (this->m_muted)
				this->m_buttonTapSFX->Play(this->m_helper);

			return;
		}
	}
	else
	{
		if (kHeld & KEY_TOUCH)
		{
			u32 j;
			hidTouchRead(&touch, j);

			if (this->m_backButton->IsPressed(&touch))
			{
				//
			}
		}
		if (kUp & KEY_TOUCH)
		{
			this->m_muteToggle->CheckIsPressed(&touch);

			if (this->m_backButton->GetPressed())
			{
				this->m_showingSettings = false;
				this->m_backButton->SetPressed(false);
				return;
			}
		}

		if (kDown & KEY_A)
		{
			this->m_muteToggle->OnValueChange();
		}

		if (this->m_muteToggle->ValueChanged())
		{
			this->m_muteToggle->ResetChangeValue();
			Mute();
			return;
		}

		if (kDown & KEY_B)
		{
			this->m_showingSettings = false;
			this->m_backButton->SetPressed(false);
			return;
		}
	}

	
	if (kDown & KEY_PLUS)
	{
		SceneManager::Instance()->ExitGame();
	}
}

// * We go to the next scene = GameScreen
void TitleScreen::NextScene()
{
	SceneManager::Instance()->LoadScene(SceneManager::GAME);
}