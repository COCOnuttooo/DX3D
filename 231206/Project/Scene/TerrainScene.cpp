#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"HeightMap/HeightMap.png");
	terrain->GetMaterial()->SetDiffuseMap(L"Landscape/Dirt3.png");
	cube = new Cube;
}

TerrainScene::~TerrainScene()
{
	delete terrain;
	delete cube;
}

void TerrainScene::Update()
{
	terrain->Update();
	cube->Update();
	if (KEY_PRESS('W'))
	{
		cube->translation += cube->GetForwardVector() * 10.0f * DELTA_TIME;
	}
	if (KEY_PRESS('S'))
	{
		cube->translation -= cube->GetForwardVector() * 10.0f * DELTA_TIME;
	}
	if (KEY_PRESS('A'))
	{
		cube->rotation.y -= DELTA_TIME;
	}
	if (KEY_PRESS('D'))
	{
		cube->rotation.y += DELTA_TIME;

	}
	cube->translation.y = LERP(cube->translation.y, terrain->GetHeight(cube->translation), 10* DELTA_TIME) ;
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	terrain->Render();
	cube->Render();
}

void TerrainScene::PostRender()
{
}
