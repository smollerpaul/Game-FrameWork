#include "pch.h"
#include "DemoScene.h"
#include "Camera.h"

#include "Textures.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Texts.h"

#include "Brick.h"
#include "Goomba.h"

DemoScene::DemoScene()
{
	LoadResources();
	Sounds::PlayLoop(SoundId::MarioMusic);
}

void DemoScene::LoadResources()
{
	const auto root = GetRootJson("Resources\\Data\\demo.json");

	map = std::make_unique<Map>( root );
	grid = std::make_unique<Grid>( root );
	mario = std::make_unique<Mario>( Vector2(10.0f, 10.0f) );
}

void DemoScene::Update(float dt)
{
	grid->UpdateCells();

	mario->Update(dt, grid->GetObjectsInViewPort());

	Camera::Instance().CenterTo( mario->GetBBox().GetCenter() );
	Camera::Instance().ClampWithin({ 0.0f, 0.0f, grid->GetWidthInPixel(), grid->GetHeightInPixel() });

	for (auto& obj : grid->GetObjectsInViewPort())
	{
		obj->Update(dt);
	}
}

void DemoScene::Draw()
{
	map->Render();
	mario->Render();

	for (auto& obj : grid->GetObjectsInViewPort())
	{
		obj->Render();
	}

	grid->RenderCells();
}

void DemoScene::OnKeyDown(BYTE keyCode)
{
	mario->OnKeyDown(keyCode);
}


