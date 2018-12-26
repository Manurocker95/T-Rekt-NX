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

#include "Dinosaur.hpp"
#include "SceneManager.hpp"
#include "Filepaths.h"
#include "Settings.hpp"

#include <random>
#include <ctime>

Dinosaur::Dinosaur(int _x, int _y, SDL_Helper * _helper, char * _sprite, char * _walkingSprite, bool _multipleFrames, int _numFramesX, int _numFramesY, int _sizePerFrameX, int _sizePerFrameY, bool _male) : Sprite (_x, _y, _helper, _sprite, _numFramesX, _numFramesY, _sizePerFrameX, _sizePerFrameY, 0, 0, _multipleFrames, true, false, 30, 44)
{
	_helper->SDL_LoadImage(&this->m_walkingSprite, _walkingSprite);

	this->m_currentDirection = Dinosaur::DIRECTION::LEFT;
	this->m_state = Dinosaur::DINOSAUR_STATE::YOUNG;
	this->m_age = 1;
	this->m_male = _male;
	this->m_alive = true;
	this->m_movement = (rand() % (DINOSAUR_MOVEMENT - 1)) + MIN_DINOSAUR_MOVEMENT;
	this->m_active = false;
	this->m_moving = false;
}

Dinosaur::~Dinosaur()
{

}


void Dinosaur::Draw(SDL_Helper * _helper)
{
	if (this->m_active)
	{
		if (!this->m_moving)
			_helper->SDL_DrawImageRect(this->m_sprite, this->m_x, this->m_y, this->m_currentFrameX * this->m_sizePerFrameX + this->m_ox, this->m_currentFrameY * this->m_sizePerFrameY + this->m_oy, this->m_sizePerFrameX - this->m_ox, this->m_sizePerFrameY - this->m_oy);
		else
			_helper->SDL_DrawImageRect(this->m_walkingSprite, this->m_x, this->m_y, this->m_currentFrameX * this->m_sizePerFrameX + this->m_ox, this->m_currentFrameY * this->m_sizePerFrameY + this->m_oy, this->m_sizePerFrameX - this->m_ox, this->m_sizePerFrameY - this->m_oy);


		if (this->m_moving)
		{
			this->m_moving = false;
			this->m_currentFrameX = 0;
		}
	
	}
}

void Dinosaur::Update()
{
	if (this->m_active)
	{
		Uint32 ticks = SDL_GetTicks();
		this->m_currentFrameX = ((ticks / (100 * DELTA_TIME_REDUCTION)) % this->m_numFramesX);

		this->m_currentFrameX += (this->m_currentDirection * m_numFramesX);		
	}
}

void Dinosaur::SetAlive(bool _value)
{
	this->m_alive = _value;
}

void Dinosaur::SetState(Dinosaur::DINOSAUR_STATE _state)
{
	this->m_state = _state;

	switch (m_state)
	{
	case Dinosaur::DINOSAUR_STATE::YOUNG:
		this->m_currentFrameY = 0;
		this->m_ox = 30;
		this->m_oy = 44;
		break;
	case Dinosaur::DINOSAUR_STATE::ADULT:
		this->m_currentFrameY = 1;
		this->m_ox = 8;
		this->m_oy = 0;
		break;
	case Dinosaur::DINOSAUR_STATE::ELDER:
		this->m_currentFrameY = 2;
		this->m_ox = 0;
		this->m_oy = 24;
		break;
	case Dinosaur::DINOSAUR_STATE::EGG:
		this->m_currentFrameY = 3;
		this->m_ox = 35;
		this->m_oy = 44;
		break;
	}
}

void Dinosaur::End(SDL_Helper * _helper)
{
	Sprite::End(_helper);
}

Dinosaur::DINOSAUR_STATE Dinosaur::GetState()
{
	return this->m_state;
}

bool Dinosaur::GetInvincible()
{
	return this->IsEgg();
}

bool Dinosaur::IsAlive()
{
	return this->m_alive;
}
bool Dinosaur::IsYoung()
{
	return this->m_state == Dinosaur::DINOSAUR_STATE::YOUNG;
}

bool Dinosaur::IsAdult()
{
	return this->m_state == Dinosaur::DINOSAUR_STATE::ADULT;
}

bool Dinosaur::IsElder()
{
	return this->m_state == Dinosaur::DINOSAUR_STATE::ELDER;
}

bool Dinosaur::IsEgg()
{
	return this->m_state == Dinosaur::DINOSAUR_STATE::EGG;
}

void Dinosaur::Die()
{
	this->m_alive = false;
}

bool Dinosaur::IsMale()
{
	return this->m_male;
}

bool Dinosaur::CanProcreate()
{
	if ((this->m_male && this->m_alive && this->m_age >= AGE_TO_BE_ADULT_MALE && this->m_age % AGE_FOR_SEX == 0) || (!this->m_male && this->m_alive && this->m_age >= AGE_TO_BE_ADULT_FEMALE && this->m_age % AGE_FOR_SEX == 0))
	{
		return true;
	}

	return false;
}

void Dinosaur::Hatch(int _x)
{
	this->m_x = _x;
	this->m_active = true;
	this->m_state = Dinosaur::DINOSAUR_STATE::EGG;
	this->m_currentDirection = Dinosaur::DIRECTION::LEFT;
	this->m_movement = (rand() % (DINOSAUR_MOVEMENT - 1)) + 1;
}


void Dinosaur::MoveX(int _value)
{
	if (this->m_active && this->m_state != Dinosaur::DINOSAUR_STATE::EGG)
	{
		this->m_moving = true;
		this->m_x += this->m_movement * _value;
		if (_value < 0)
			SetDirection(Dinosaur::DIRECTION::LEFT);
		else
			SetDirection(Dinosaur::DIRECTION::RIGHT);
	}
}

void  Dinosaur::SetDirection(Dinosaur::DIRECTION _direction)
{
	this->m_currentDirection = _direction;
}