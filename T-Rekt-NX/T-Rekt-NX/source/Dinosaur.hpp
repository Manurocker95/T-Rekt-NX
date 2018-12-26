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


#ifndef _DINOSAUR_HPP_
#define _DINOSAUR_HPP_

#include "SDL_Helper.hpp"
#include "Sprite.hpp"

class Dinosaur : public Sprite
{
public:
	enum DINOSAUR_STATE 
	{ 
		YOUNG = 0, 
		ADULT = 1, 
		ELDER = 2,
		EGG = 3
	};

	enum DIRECTION
	{
		LEFT = 0,
		RIGHT = 1,
	};

private:
	SDL_Texture * m_walkingSprite;
	DINOSAUR_STATE m_state;
	DIRECTION m_currentDirection;
	int m_age;
	int m_movement;
	bool m_male;	
	bool m_alive;
	bool m_moving;
	bool m_goToIdle;
public:

	Dinosaur(int _x, int _y, SDL_Helper * _helper, char * _sprite, char * _walkingSprite, bool _multipleFrames, int _numFramesX, int _numFramesY, int _sizePerFrameX, int _sizePerFrameY, bool _male);
	~Dinosaur();

	void MoveX(int _value) override;

	void Draw(SDL_Helper * _helper) override;
	void Update() override;
	void End(SDL_Helper * _helper) override;

	DINOSAUR_STATE GetState();
	void SetState(DINOSAUR_STATE _value);

	bool GetInvincible();

	bool IsAlive();
	bool IsYoung();
	bool IsAdult();
	bool IsElder();
	bool IsEgg();

	void Die();
	bool IsMale();
	bool CanProcreate();
	void Hatch(int _x);
	void SetAlive(bool _value);
	void SetDirection(DIRECTION _direction);
	void YearPassed();
};

#endif