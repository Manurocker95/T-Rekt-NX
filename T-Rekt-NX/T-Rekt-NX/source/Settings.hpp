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
#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#define PROJECT_NAME "Whats In The Box"

// Screen size: 1280x720
#define SWITCH_SCREEN_WIDTH 1280
#define SWITCH_SCREEN_HEIGHT 720

// Version of our Homebrew and if we want to set a debugmode for us. 
// We can disable it from here.
#define VERSION "1.0"

// Time wait in loading screen in seconds
#define LOADING_DELAY 2 

// HALF TIME -> SDL_TICKS/(100*reduction)
#define DELTA_TIME_REDUCTION 2

#define SCORE_TO_ADD 1
#define SCORE_TO_ADD_WHEN_PROCREATE 5

// Game Settings
#define MAX_NUMBER_OF_DINOS 10
#define NUMBER_PROCREATION 3
#define STARTING_DINOSAURS 5
#define DINOSAUR_MOVEMENT 15
#define MIN_DINOSAUR_MOVEMENT 5
#define PIXELS_BETWEEN_DINOS 240

//Ages Male
#define AGE_TO_BE_ADULT_MALE 40
#define AGE_TO_BE_OLD_MALE 90
#define AGE_TO_DIE_MALE 100

//Ages Female
#define AGE_TO_BE_ADULT_FEMALE 20
#define AGE_TO_BE_OLD_FEMALE 90
#define AGE_TO_DIE_FEMALE 100

//Ages to have babys... If you know what I mean
#define AGE_FOR_SEX 30

//Meteorite settings
#define NUMBER_OF_METEOS 10
#define METEORITE_MOVEMENT 3
#define METEORITE_SCORE 1

#define DINO_MIN_POS_X 100
#define FLOOR_POS 720

#define TIME_TO_START 4
#define FRAMES_PER_YEAR 1000 // a second

#define SPAWN_MIN_X 100
#define SPAWN_MAX_X 1100

#define ROUNDS_MULTIPLIER 2

class Settings
{
public:
	
	bool m_debugMode;
	bool m_muted;
	bool m_paused;

public:

	Settings() 
	{
		this->m_muted = false;
		this->m_debugMode = false;
		this->m_paused = false;
	}

	void SetMute(bool _value)
	{
		this->m_debugMode = _value;
	}

	void ToggleMute()
	{
		this->m_muted = !this->m_muted;
	}
	
	void TogglePause()
	{
		this->m_paused = !this->m_paused;
	}
};
#endif