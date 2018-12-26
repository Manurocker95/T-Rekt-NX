#pragma once
#ifndef _METEORITE_HPP_
#define _METEORITE_HPP_

#include "Sprite.hpp"

class Meteorite : public Sprite
{

private:

	bool m_fellDown;
	bool m_falling;
	float m_speed;


public:

	Meteorite(int _x, int _y, SDL_Helper * _helper, char * _sprite, int _sizePerFrameX, int _sizePerFrameY);
	~Meteorite();

	void Update() override;
	void ResetValue();
	void SetSpeed(float _value);
	bool GetFalling();
	void SetFalling(bool _value);
	bool FellDown();
};

#endif
