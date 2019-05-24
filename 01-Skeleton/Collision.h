#pragma once
#include "GameObject.h"

struct CollisionEvent
{
	float	      t      = 1.0f   ;
	float	      nx     = 0.0f   ; // specific 'swept aabb' naming convention
	float	      ny     = 0.0f   ; 
	LPCGAMEOBJECT pCoObj = nullptr; // pointer to object collide with

	CollisionEvent() noexcept = default;
	CollisionEvent(float t, float nx, float ny, const GameObject& coObj) : t(t), nx(nx), ny(ny), pCoObj(&coObj) {}
	CollisionEvent(float t, float nx, float ny) : t(t), nx(nx), ny(ny) {}
	operator bool() const { return pCoObj != nullptr; }
};


struct CollisionDetector
{
	static RECT GetBroadPhaseBox(const RECT& rect, float dx, float dy);
	static CollisionEvent SweptAABBEx(const GameObject& obj1, const GameObject& obj2, float dt);
	static std::vector<CollisionEvent> CalcPotentialCollisions(const GameObject& obj, const std::vector<LPCGAMEOBJECT>& coObjs, float dt);
	static std::vector<CollisionEvent> FilterCollisions(std::vector<CollisionEvent> preFilter, float& min_tx, float& min_ty, float& nx, float&ny);
};