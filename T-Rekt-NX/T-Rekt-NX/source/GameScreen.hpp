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


#pragma once
#ifndef _GAME_SCREEN_HPP_
#define _GAME_SCREEN_HPP_
#include <string>
#include "Scene.hpp"
#include "MusicSound.hpp"
#include "SfxSound.hpp"
#include "Text.hpp"
#include "Dinosaur.hpp"
#include <vector>

class GameScreen : public Scene
{

private:

	Text * m_scoreText;
	Text * m_roundsText;
	//Images
	Sprite * m_background;
	Sprite * m_pauseBG;
	//Dinosaurs
	std::vector < Dinosaur * > m_dinosaurs;
	std::vector < Dinosaur * > m_aliveDinosaurs;

	MusicSound * m_gameBGM;
	SfxSound * m_tapSFX;

	bool m_debugMode;
	bool m_dragging;
	bool m_maleAlive;
	bool m_femaleAlive;
	int m_score;
	int m_spawned;
	int m_maxSpawn;
	int m_solved;
	int m_rounds;
	float m_speedMultiplier;

	unsigned int m_currentTime;
	unsigned int m_lastTime;
	unsigned int m_timeToSpawn;
public:

	GameScreen(Settings * settings);							// Constructor
	~GameScreen();												// Destructor
	void Start(SDL_Helper * helper) override;					// initialize
	void Draw() override;										// Draw
	void CheckInputs(u64 kDown, u64 kHeld, u64 kUp) override;	// CheckInput
	void Update() override;										// Update
	void NextScene() override;
	void EndGame();
	void AddScore();
	void Spawn();
	void Procreate();
};

#endif