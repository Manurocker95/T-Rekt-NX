#include "Meteorite.hpp"
#include "Settings.hpp"

Meteorite::Meteorite(int _x, int _y, SDL_Helper * _helper, char * _sprite, int _sizePerFrameX, int _sizePerFrameY) : Sprite(_x, _y, _helper, _sprite, 5, 1, _sizePerFrameX, _sizePerFrameY, 0, 0, true, true, false, 0, 0)
{
	this->m_active = false;
	this->m_fellDown = false;
	this->m_falling = false;
	this->m_speed = 1.f;
}


Meteorite::~Meteorite()
{

}

void Meteorite::Update()
{
	if (!this->m_active)
	{
		return;
	}

	Sprite::Update();

	if (this->m_falling)
	{
		this->m_y += METEORITE_MOVEMENT * m_speed;
	}

	if (this->m_y > SWITCH_SCREEN_HEIGHT + this->m_sizePerFrameY)
	{
		this->m_active = false;
		this->m_fellDown = true;
	}	
}

void Meteorite::ResetValue()
{
	this->m_y = -m_sizePerFrameY;
	this->m_fellDown = false;
	this->m_falling = false;
}

void Meteorite::SetSpeed(float _value)
{
	this->m_speed = _value;
}

bool Meteorite::GetFalling()
{
	return this->m_falling;
}

void Meteorite::SetFalling(bool _value)
{
	this->m_falling = _value;
}

bool Meteorite::FellDown()
{
	return this->m_fellDown;
}