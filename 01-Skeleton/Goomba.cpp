#include "pch.h"
#include "Goomba.h"
#include "MainWindow.h"

Goomba::Goomba(const Point & spawnPos) :
	GameObject(State::GoombaMoving, spawnPos, { -50.0f, 0.0f })
{
	animations.emplace(State::GoombaMoving, Animation(SpriteType::GoombaMoving, 0.1f));
	animations.emplace(State::GoombaDie   , Animation(SpriteType::GoombaDie   , 0.1f));
}

void Goomba::Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects)
{
	static const MainWindow& wnd = MainWindow::Instance();
	if (curState == State::GoombaDie) return;

	pos.x += vel.x * dt;
	pos.y += vel.y * dt;

	if (pos.x < 0.0f) {
		pos.x = 0.0f;
		vel.x = - vel.x;
	} 
	else if (pos.x > wnd.GetWidth() - GetWidth()) {
		pos.x = (float)wnd.GetWidth() - GetWidth();
		vel.x = - vel.x;
	}

	animations.at(curState).Update(dt);
}

void Goomba::SetState(State state)
{
	auto oldHeight = GetHeight();

	GameObject::SetState(state);
	switch (state)
	{
		case State::GoombaDie:
			LowDownBody(oldHeight);
			vel.x = 0.0f;
			break;

	}
}
