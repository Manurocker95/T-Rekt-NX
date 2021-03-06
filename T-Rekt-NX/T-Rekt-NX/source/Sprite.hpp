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
#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include "SDL_Helper.hpp"

class Sprite
{
protected:
	SDL_Texture * m_sprite;
	int m_x;
	int m_y;
	int m_ox;
	int m_oy;
	int m_numFramesX;
	int m_numFramesY;
	int m_sizePerFrameX;
	int m_sizePerFrameY;
	int m_currentFrameX;
	int m_currentFrameY;
	int m_opacity;
	bool m_updateYFrame;
	bool m_multipleFrames;
	bool m_active;
	bool m_animated;
	bool m_drawOpacity;
	bool m_inLoop;

public:
	Sprite(int _x, int _y, SDL_Helper * _helper, char * _sprite, int _numFramesX, int _numFramesY, int _sizePerFrameX, int _sizePerFrameY, int _currentFrameX, int _currentFrameY, bool _multipleFrames, bool _animated, bool _opacityMode = false, int _ox = 0, int _oy = 0);
	~Sprite() {};
	virtual void MoveX(int _value);
	virtual void MoveY(int _value);
	virtual void MoveToCoord(int _x, int _y);

	virtual int GetX();
	virtual void SetX(int _value);
	virtual int GetY();
	virtual void SetY(int _value);
	virtual int GetOX();
	virtual void SetOX(int _value);
	virtual int GetOY();
	virtual void SetOY(int _value);

	virtual SDL_Texture * GetSprite();
	virtual void SetSprite(SDL_Texture * _sprite);

	virtual void Draw(SDL_Helper * _helper);
	virtual void Update();
	virtual void End(SDL_Helper * _helper);

	virtual void SetNumFrames(int _value);
	virtual int GetNumFramesX();
	virtual int GetNumFramesY();
	virtual void SetFrameSize(int _value, bool _xAxis);
	virtual int GetFrameSize(bool _xAxis);

	virtual bool Touched(touchPosition * _touch);
	virtual bool IsActive();
	virtual void SetActive(bool _value);
	virtual bool IsLoop();
	virtual void SetInLoop(bool _value);
	virtual bool IsAnimated();
	virtual void SetOpacity(int _value);
	virtual void SetOpacityMode(bool _value);

	virtual bool CheckOverlap(Sprite * _other);
};
#endif