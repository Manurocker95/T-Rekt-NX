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
	this->m_changeScene = false;
	this->m_muted = false;
	this->m_dragging = false;
	this->m_score = 0;
	this->m_speedMultiplier = 1.f;
	this->m_spawned = 0;
	this->m_solved = 0;
	this->m_maxSpawn = 1;
	this->m_rounds = 1;
	this->m_currentTime = SDL_GetTicks();
	srand(time(NULL));


}

GameScreen::~GameScreen()
{
	this->m_background->End(this->m_helper);
	delete(this->m_background);

	this->m_gameBGM->End(this->m_helper);
	delete(this->m_gameBGM);

	this->m_tapSFX->End(this->m_helper);
	delete(this->m_tapSFX);

	this->m_scoreText->End(this->m_helper);
	delete(this->m_scoreText);	
	
	this->m_roundsText->End(this->m_helper);
	delete(this->m_roundsText);

	for (const auto & dino : this->m_dinosaurs)
	{
		dino->End(this->m_helper);
		delete(dino);
	}
}

void GameScreen::Start(SDL_Helper * helper)
{
	this->m_helper = helper;
	this->m_scoreText = new Text(helper, "Score: 0", 525, 20, 15, true, FONT_NORMAL, BLACK);
	this->m_roundsText = new Text(helper, "Rounds: 0", 155, 20, 15, true, FONT_NORMAL, BLACK);
	this->m_background = new Sprite(0, 0, helper, IMG_BACKGROUND, 2, 4, SWITCH_SCREEN_WIDTH, SWITCH_SCREEN_HEIGHT, 0, 0, true, true, false);
	this->m_gameBGM = new MusicSound(this->m_helper, SND_BGM_GAME, true, 1);
	this->m_tapSFX = new SfxSound(this->m_helper, SND_SFX_TAP, false, 2);
	this->m_gameBGM->Play(this->m_helper);
	
	if (this->m_muted)
		this->m_helper->SDL_PauseMusic();

	this->m_dinosaurs.reserve(MAXNUMBEROFDINOS);
	
	int m_space = 0;
	//140x140
	for (int i = 0; i < MAXNUMBEROFDINOS; i++)
	{
		u16 gender = rand() % 100;

		if (i < MAXNUMBEROFDINOS / 2)
		{
			if (gender % 2 == 0)
			{
				m_dinosaurs.push_back(new Dinosaur(DINO_MIN_POS_X + m_space, FLOOR_POS - 140, helper, IMG_DINO_SPRITE, false, 5, 1, 80, 140, true));
			}
			else
			{
				m_dinosaurs.push_back(new Dinosaur(DINO_MIN_POS_X + m_space, FLOOR_POS - 140, helper, IMG_DINO_SPRITE_F, false, 5, 1, 80, 140, false));
			}
		}
		else
		{
			if (gender % 4 == 0)
			{
				m_dinosaurs.push_back(new Dinosaur(DINO_MIN_POS_X + m_space, FLOOR_POS - 140, helper, IMG_DINO_SPRITE, false, 5, 1, 80, 140, true));
			}
			else
			{
				m_dinosaurs.push_back(new Dinosaur(DINO_MIN_POS_X + m_space, FLOOR_POS - 140, helper, IMG_DINO_SPRITE_F, false, 5, 1, 80, 140, false));
			}
		}

		m_space += PIXELSBETWEENDINOS;
	}
}

void GameScreen::EndGame()
{
	this->m_changeScene = true;
}

void GameScreen::Draw()
{
	this->m_background->Draw(this->m_helper);


	for (const auto & dino : this->m_dinosaurs)
	{
		dino->Draw(this->m_helper);
	}

	this->m_scoreText->Draw(this->m_helper);
	this->m_roundsText->Draw(this->m_helper);
}

void GameScreen::Update()
{
	if (!this->m_paused)
	{
		this->m_background->Update();

		for (const auto & dino : this->m_dinosaurs)
		{
			dino->Update();
		}

		if (m_spawned > 0 && m_solved > 0)
		{

		}
		else
		{
			this->m_currentTime = SDL_GetTicks();

			if (this->m_currentTime >= this->m_timeToSpawn + this->m_lastTime)
			{
				this->m_lastTime = this->m_currentTime;
				Spawn();
			}
		}
	}

	if (this->m_changeScene)
		NextScene();
}

void GameScreen::CheckInputs(u64 kDown, u64 kHeld, u64 kUp)
{
	if (kDown & KEY_MINUS)
	{
		this->m_paused = !m_paused;
	}
		
	if (!this->m_paused)
	{
		if (kHeld & KEY_RIGHT)
		{
			for (const auto & dino : this->m_dinosaurs)
			{
				if (dino->IsActive())
					dino->MoveX(1);
			}
		}
		else if (kHeld & KEY_LEFT)
		{
			for (const auto & dino : this->m_dinosaurs)
			{
				if (dino->IsActive())
					dino->MoveX(-1);
			}
		}
	}

	if (kDown & KEY_PLUS)
		EndGame();
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


	this->m_roundsText->SetText("Rounds: " + std::to_string(this->m_rounds));
}


void GameScreen::Procreate()
{
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
				++this->m_dinosAlive;
			}
		}

	}
}