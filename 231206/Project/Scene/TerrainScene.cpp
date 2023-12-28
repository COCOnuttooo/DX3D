#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
<<<<<<< HEAD
	terrain = new Terrain(L"HeightMap/HeightMap.png");
	terrain->GetMaterial()->SetDiffuseMap(L"Landscape/Dirt3.png");
	terrain->translation.y = -0.1;
=======
	terrain = new Terrain(L"HeightMap/HeightMap256.png");
	
	terrain->GetMaterial()->SetDiffuseMap(L"Landscape/Dirt2.png");
	terrain->GetMaterial()->SetSpecularMap(L"Landscape/Wall_specular.png");
	terrain->GetMaterial()->SetNormalMap(L"Landscape/Wall_normal.png");
>>>>>>> 4df3ed510b5898a2e30b2da156bac28ec4f09b9f
	cube = new Cube;
	ENVIRONMENT->GetCamera()->SetParent(cube);
	ENVIRONMENT->GetCamera()->translation = Vector3(0, 20, 0);
	ENVIRONMENT->GetCamera()->rotation = Vector3(XM_PIDIV2, 0, 0);
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
	cube->translation.y = terrain->GetHeight(cube->translation) +0.5; //LERP(cube->translation.y, terrain->GetHeight(cube->translation), 10* DELTA_TIME) ;
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
