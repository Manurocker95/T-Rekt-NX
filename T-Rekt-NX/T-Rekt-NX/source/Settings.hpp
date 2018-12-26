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

#define DELTA_TIME_REDUCTION 1 // HALF TIME -> SDL_TICKS/(100*reduction)

#define SCORE_TO_ADD 1
#define SCORE_TO_ADD_WHEN_PROCREATE 5

// Game Settings
#define MAXNUMBEROFDINOS 10
#define NUMBER_PROCREATION 3
#define STARTINGDINOSAURS 5
#define DINOSAURMOVEMENT 10
#define PIXELSBETWEENDINOS 240

//Ages Male
#define AGETOBEADULTMALE 4000
#define AGETOBEOLDMALE 9000
#define AGETODIEMALE 10000

//Ages Female
#define AGETOBEADULTFEMALE 4000
#define AGETOBEOLDFEMALE 9000
#define AGETODIEFEMALE 10000

//Ages to have babys... If you know what I mean
#define AGEFORSEX 2500

//Meteorite settings
#define NUMOFMETEOS 10
#define METEORITEMOVEMENT 3
#define METEORITESCORE 1

#define DINO_MIN_POS_X 100
#define FLOOR_POS 768

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