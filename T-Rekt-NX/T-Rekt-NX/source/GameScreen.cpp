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


#include "GameScreen.hpp"
#include "SceneManager.hpp"
#include "Colors.h"
#include "Filepaths.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

GameScreen::GameScreen(Settings * settings) : Scene(settings)
{
	settings->SetMute(false);
	this->m_paused = false;
	this->m_startGame = false;
	this->m_dragging = false;
	this->m_updateYear = false;
	this->m_timeToProcreate = 0;
	this->m_score = 0;
	this->m_speedMultiplier = 1.f;
	this->m_spawned = 0;
	this->m_solved = 0;
	this->m_maxSpawn = 1;
	this->m_rounds = 0;
	this->m_timeToStart = 0;
	this->m_timeToSpawn = 0;
	this->m_lastTime = 0;
	this->m_currentTime = SDL_GetTicks();
	srand(time(NULL));


}

GameScreen::~GameScreen()
{
	this->m_background->End(this->m_helper);
	delete(this->m_background);	
	
	this->m_muteToggle->End(this->m_helper);
	delete(this->m_muteToggle);
		
	this->m_pauseBG->End(this->m_helper);
	delete(this->m_pauseBG);

	this->m_gameBGM->End(this->m_helper);
	delete(this->m_gameBGM);

	this->m_tapSFX->End(this->m_helper);
	delete(this->m_tapSFX);

	this->m_scoreText->End(this->m_helper);
	delete(this->m_scoreText);	
	
	this->m_roundsText->End(this->m_helper);
	delete(this->m_roundsText);	
	
	this->m_pauseBtn->End(this->m_helper);
	delete(this->m_pauseBtn);	
	
	this->m_exitBtn->End(this->m_helper);
	delete(this->m_exitBtn);
	
	this->m_debugText->End(this->m_helper);
	delete(this->m_debugText);

	this->m_aliveDinosaurs.clear();

	for (const auto & dino : this->m_dinosaurs)
	{
		dino->End(this->m_helper);
		delete(dino);
	}
	this->m_dinosaurs.clear();

	this->m_fallingMeteos.clear();

	for (const auto & meteo : this->m_meteos)
	{
		meteo->End(this->m_helper);
		delete(meteo);
	}
	this->m_meteos.clear();
}

void GameScreen::Start(SDL_Helper * helper)
{
	this->m_helper = helper;
	this->m_scoreText = new Text(helper, "Score: 0", 525, 20, 15, true, FONT_NORMAL, BLACK);
	this->m_roundsText = new Text(helper, "Rounds: 0", 155, 20, 15, true, FONT_NORMAL, BLACK);
	this->m_infoText = new Text(helper, "", 455, 420, 125, true, FONT_NORMAL, BLUE);
	this->m_debugText = new Text(helper, "DEBUG MODE ON", 455, 680, 25, true, FONT_NORMAL, BLUE);
	this->m_background = new Sprite(0, 0, helper, IMG_BACKGROUND, 2, 4, SWITCH_SCREEN_WIDTH, SWITCH_SCREEN_HEIGHT, 0, 0, true, true, false);
	this->m_pauseBG = new Sprite(0, 0, helper, IMG_PAUSED, 2, 4, SWITCH_SCREEN_WIDTH, SWITCH_SCREEN_HEIGHT, 0, 0, true, true, false);
	this->m_gameBGM = new MusicSound(helper, SND_BGM_GAME, true, 1);
	this->m_tapSFX = new SfxSound(helper, SND_SFX_TAP, false, 2);
	this->m_dinoScream = new SfxSound(helper, SND_SFX_DINO_SCREAM, false, 3);
	this->m_gameBGM->Play(helper);
	
	this->m_exitBtn = new Button(30, 60, helper, IMG_BTN_EXIT, IMG_BTN_EXIT_NON_INTERACTABLE, IMG_BTN_EXIT_PRESSED, true, false, 1, 1, 74, 74, false, 0, 0);
	this->m_pauseBtn = new Button(1000, 60, helper, IMG_BTN_PAUSE, IMG_BTN_PAUSE_NON_INTERACTABLE, IMG_BTN_PAUSE_PRESSED, true, false, 1, 1, 74, 74, false, 0, 0);
	this->m_pauseBtn->SetInteractable(false);

	this->m_muteToggle = new Toggle(this->m_muted, 1110, 60, helper, IMG_TOGGLE_INGAME_MUTE_ON, IMG_TOGGLE_INGAME_MUTE_OFF, true, false, 1, 1, 74, 74, false, 0, 0);

	if (this->m_muted)
		helper->SDL_PauseMusic();

	// allocate vector
	this->m_dinosaurs.reserve(MAX_NUMBER_OF_DINOS);
	Dinosaur * dino;
	int m_space = 0;
	//144x144 
	for (int i = 0; i < MAX_NUMBER_OF_DINOS; i++)
	{
		int gender = rand() % 100;

		if (i < MAX_NUMBER_OF_DINOS / 2)
			dino = (gender % 2 == 0) ? new Dinosaur(DINO_MIN_POS_X + m_space, FLOOR_POS - 144, helper, IMG_DINO_SPRITE, IMG_DINO_SPRITE_WALKING, true, 4, 1, 144, 144, true) : new Dinosaur(DINO_MIN_POS_X + m_space, FLOOR_POS - 144, helper, IMG_DINO_SPRITE_F, IMG_DINO_SPRITE_F_WALKING, true, 4, 1, 144, 144, false);
		else
			dino = (gender % 4 == 0) ? new Dinosaur(DINO_MIN_POS_X + m_space, FLOOR_POS - 144, helper, IMG_DINO_SPRITE, IMG_DINO_SPRITE_WALKING, true, 4, 1, 144, 144, true) : new Dinosaur(DINO_MIN_POS_X + m_space, FLOOR_POS - 144, helper, IMG_DINO_SPRITE_F, IMG_DINO_SPRITE_F_WALKING, true, 4, 1, 144, 144, false);

		this->m_dinosaurs.push_back(dino);
		m_space += PIXELS_BETWEEN_DINOS;

	}

	this->m_aliveDinosaurs.reserve(MAX_NUMBER_OF_DINOS);
	for (int j = 0; j < STARTING_DINOSAURS; j++)
	{
		this->m_dinosaurs[j]->SetActive(true);
		this->m_aliveDinosaurs.push_back(this->m_dinosaurs[j]);
	}

	int meteoSpace = SWITCH_SCREEN_WIDTH / NUMBER_OF_METEOS;
	this->m_meteos.reserve(NUMBER_OF_METEOS);
	for (int i = 0; i < NUMBER_OF_METEOS; i++)
	{
		m_meteos.push_back(new Meteorite(meteoSpace*i, -141, helper, IMG_METEORITE, 120, 141));
	}
}

void GameScreen::EndGame()
{
	this->m_changeScene = true;
}

void GameScreen::Draw()
{
	this->m_background->Draw(this->m_helper);

	for (const auto & dino : this->m_aliveDinosaurs)
		dino->Draw(this->m_helper);

	for (const auto & meteo : m_fallingMeteos)
		meteo->Draw(this->m_helper);

	this->m_scoreText->Draw(this->m_helper);
	this->m_roundsText->Draw(this->m_helper);

	if (!this->m_startGame)
		this->m_infoText->Draw(this->m_helper);

	if (this->m_paused)
		this->m_pauseBG->Draw(this->m_helper);

	this->m_muteToggle->Draw(this->m_helper);
	this->m_pauseBtn->Draw(this->m_helper);
	this->m_exitBtn->Draw(this->m_helper);

	if (this->m_debugMode)
		this->m_debugText->Draw(this->m_helper);
}

void GameScreen::Update()
{
	if (!this->m_paused)
	{
		this->m_background->Update();

		this->m_currentTime = SDL_GetTicks();

		if (this->m_currentTime > this->m_lastTime + 1000) 
		{
			this->m_lastTime = this->m_currentTime;
			
			if (!this->m_startGame)
			{
				++this->m_timeToStart;

				if (this->m_timeToStart >= TIME_TO_START)
				{
					this->m_startGame = true;
					this->m_pauseBtn->SetInteractable(true);
				}
			}	
			else
			{
				++this->m_timeToProcreate;
				if (this->m_timeToProcreate >= AGE_FOR_SEX)
					Procreate();
			}
		}

		if (!this->m_startGame)
		{
			switch (this->m_timeToStart)
			{
			case 1:
				this->m_infoText->SetText("Avoid the meteorites");
				this->m_infoText->MoveToCoord(55, 300);
				break;
			case 2:
				this->m_infoText->SetText("Ready??");
				this->m_infoText->SetX(455);
				break;
			case 3:
				this->m_infoText->SetText("Go!!!!!");
				this->m_infoText->SetX(455);
				break;
			}
		}
		else
		{
			if (this->m_fallingMeteos.size() == 0)
			{
				Spawn();
			}
			else
			{
				for (int j = 0; j < this->m_fallingMeteos.size(); j++)
				{
					if (this->m_fallingMeteos.at(j) == NULL)
						continue;

					if (this->m_fallingMeteos.at(j)->FellDown())
					{
						AddScore();
						this->m_fallingMeteos.at(j)->ResetValue();
						this->m_fallingMeteos.erase(this->m_fallingMeteos.begin() + j);
						continue;
					}
					this->m_fallingMeteos.at(j)->Update();

					for (int k = 0; k < this->m_aliveDinosaurs.size(); k++)
					{
						if (this->m_aliveDinosaurs.at(k) == NULL)
							continue;

						if (this->m_fallingMeteos.at(j)->CheckOverlap(this->m_aliveDinosaurs.at(k)))
						{
							if (!this->m_muted)
								this->m_dinoScream->Play(this->m_helper);

							this->m_aliveDinosaurs.at(k)->SetAlive(false);
							this->m_aliveDinosaurs.at(k)->SetActive(false);
							this->m_aliveDinosaurs.erase(this->m_aliveDinosaurs.begin() + k);
						}
					}		

					if (this->m_aliveDinosaurs.size() < 1)
					{
						this->m_paused = true;
						SceneManager::Instance()->SaveData(this->m_score);
						EndGame();
						break;
					}
				}
			}

			this->m_updateYear = (this->m_currentTime >  this->m_lastTime + FRAMES_PER_YEAR) ? true : false;

			for (int i = 0; i < this->m_aliveDinosaurs.size(); i++)
			{
				if (this->m_updateYear)
				{
					if (this->m_aliveDinosaurs.at(i) == NULL)
						continue;

					this->m_aliveDinosaurs.at(i)->YearPassed();
					// if has died
					if (!this->m_aliveDinosaurs.at(i)->IsAlive())
					{
						this->m_aliveDinosaurs.erase(this->m_aliveDinosaurs.begin() + i);
						continue;
					}
				}

				this->m_aliveDinosaurs.at(i)->Update();

			}
		}
	}

	if (this->m_changeScene)
		NextScene();
}

void GameScreen::CheckInputs(u64 kDown, u64 kHeld, u64 kUp)
{
	if (kDown & KEY_R)
	{
		this->m_debugMode = !this->m_debugMode;
	}

	if (kDown & KEY_MINUS)
	{
		this->m_paused = !this->m_paused;
	}
	
	if (kHeld & KEY_TOUCH)
	{
		u32 j;
		hidTouchRead(&touch, j);

		this->m_pauseBtn->IsPressed(&touch);
		this->m_exitBtn->IsPressed(&touch);
	}
	else if (kUp & KEY_TOUCH)
	{
		this->m_muteToggle->CheckIsPressed(&touch);

		if (this->m_pauseBtn->GetPressed())
		{
			this->m_paused = !this->m_paused;
			this->m_pauseBtn->SetPressed(false);
			return;
		}		
		
		if (this->m_exitBtn->GetPressed())
		{
			this->m_exitBtn->SetPressed(false);
			EndGame();
			return;
		}

		if (this->m_muteToggle->ValueChanged())
		{
			this->m_muteToggle->ResetChangeValue();
			Mute();
			return;
		}
	}

	if (kDown & KEY_PLUS)
	{
		EndGame();
		return;
	}
		
	if (!this->m_startGame)
		return;

	if (!this->m_paused)
	{
		if (kHeld & KEY_RIGHT)
		{
			for (const auto & dino : this->m_aliveDinosaurs)
			{
				if (dino->IsActive())
					dino->MoveX(1);
			}
		}
		else if (kHeld & KEY_LEFT)
		{
			for (const auto & dino : this->m_aliveDinosaurs)
			{
				if (dino->IsActive())
					dino->MoveX(-1);
			}
		}
	}
	else
	{
		if (kDown & KEY_B)
		{
			this->m_paused = false;
		}
	}
}

// * We go to the next scene = GameScreen
void GameScreen::NextScene()
{	
	SceneManager::Instance()->SaveData(m_score);
	SceneManager::Instance()->LoadScene(SceneManager::SCENES::TITLE);
}

void GameScreen::AddScore()
{
	--this->m_solved;
	this->m_score += SCORE_TO_ADD;
	this->m_scoreText->SetText("Score: " + std::to_string(this->m_score));
}

void GameScreen::Spawn()
{
	++this->m_rounds;
	this->m_roundsText->SetText("Rounds: " + std::to_string(this->m_rounds));

	this->m_spawned = rand() % this->m_maxSpawn + 1; // Between 1 and Max
	this->m_solved = this->m_spawned;

	int num = 0;
	for (int i = 0; i < m_spawned; i++)
	{
		num = rand() % (NUMBER_OF_METEOS-1) + 1;

		if (!this->m_meteos.at(num)->GetFalling())
		{
			this->m_meteos.at(num)->SetFalling(true);
			this->m_meteos.at(num)->SetActive(true);
			this->m_fallingMeteos.push_back(m_meteos.at(num));
		}
	}

	++this->m_rounds;

	if (this->m_rounds % ROUNDS_MULTIPLIER == 0)
		++this->m_maxSpawn;

	if (m_maxSpawn >= NUMBER_OF_METEOS)
		m_maxSpawn = NUMBER_OF_METEOS-1;
}


void GameScreen::Procreate()
{
	this->m_timeToProcreate = 0;
	this->m_femaleAlive = false;
	this->m_maleAlive = false;
	int _x = 0;

	std::vector<Dinosaur*> _notActive;

	for (const auto & dino : this->m_dinosaurs)
	{
		if (!dino->IsActive())
		{
			_notActive.push_back(dino);
			continue;
		}

		// If there's a female 
		if (!this->m_femaleAlive && !dino->IsMale())
		{
			_x = dino->GetX();
			this->m_femaleAlive = true;
		}			

		// If there's a female 
		if (!this->m_maleAlive && dino->IsMale())
			this->m_maleAlive = true;
	}

	if (this->m_femaleAlive && this->m_maleAlive)
	{
		// How many dinos can be 
		int dinos = rand() % NUMBER_PROCREATION;
		int dinoCount = 0;

		for (const auto & dino : _notActive)
		{
			if (dinoCount < dinos)
			{
				dino->Hatch(_x);
				++dinoCount;
				this->m_score += SCORE_TO_ADD_WHEN_PROCREATE;
				this->m_aliveDinosaurs.push_back(dino);
			}
		}

	}
}