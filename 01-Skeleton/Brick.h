#pragma once
#include "GameObject.h"

class Brick : public GameObject
{
public:
	Brick(const D3DXVECTOR3 & pos) :
		GameObject(State::BrickIdle, pos, 16, 16)
	{
		animations.emplace(State::BrickIdle, Animation(SpriteType::BrickIdle, std::numeric_limits<float>::infinity()));
	}
};