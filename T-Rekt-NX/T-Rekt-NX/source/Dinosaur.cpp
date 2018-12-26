/* This file is part of T-Rekt NX!

Copyright (C) 2018/2019 Manuel Rodr�guez Matesanz
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

Dinosaur::Dinosaur(int _x, int _y, SDL_Helper * _helper, char * _sprite, bool _multipleFrames, int _numFramesX, int _numFramesY, int _sizePerFrameX, int _sizePerFrameY, bool _male) : Sprite (_x, _y, _helper, _sprite, _numFramesX, _numFramesY, _sizePerFrameX, _sizePerFrameY, 0, 0, _multipleFrames, true, false)
{
	this->m_currentDirection = Dinosaur::DIRECTION::LEFT;
	this->m_state = Dinosaur::DINOSAUR_STATE::YOUNG;
	this->m_age = 1;
	this->m_male = _male;
	this->m_alive = true;
	this->m_invincible = false;
	this->m_originalX = _x;
	this->m_originalY = _y;
	this->m_movement = (rand() % (DINOSAURMOVEMENT - 1)) + 1;
}

Dinosaur::~Dinosaur()
{

}

void Dinosaur::SetState(Dinosaur::DINOSAUR_STATE _state)
{
	this->m_state = _state;

	switch (m_state)
	{
	case Dinosaur::DINOSAUR_STATE::YOUNG:
		this->m_currentFrameY = 0;
		break;
	case Dinosaur::DINOSAUR_STATE::ADULT:
		this->m_currentFrameY = 1;
		break;
	case Dinosaur::DINOSAUR_STATE::ELDER:
		this->m_currentFrameY = 2;
		break;
	case Dinosaur::DINOSAUR_STATE::EGG:
		this->m_currentFrameY = 3;
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

void Dinosaur::SetInvincible(bool _value)
{
	this->m_invincible = _value;
}

bool Dinosaur::GetInvincible()
{
	return this->m_invincible;
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

void Dinosaur::Reset()
{
	this->m_x = this->m_originalX;
	this->m_y = this->m_originalY;
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
	if ((this->m_male && this->m_alive && this->m_age >= AGETOBEADULTMALE && this->m_age % AGEFORSEX == 0) || (!this->m_male && this->m_alive && this->m_age >= AGETOBEADULTFEMALE && this->m_age % AGEFORSEX == 0))
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
	this->m_movement = (rand() % (DINOSAURMOVEMENT - 1)) + 1;
}

void Dinosaur::MoveX(int _value)
{
	this->m_x += this->m_movement * _value;
}