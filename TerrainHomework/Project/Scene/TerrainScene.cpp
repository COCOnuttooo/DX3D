#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"HeightMap/HeightMap.png");
	terrain->GetMaterial()->SetDiffuseMap(L"Landscape/Dirt3.png");
	bot = new HomeworkBot;
	ENVIRONMENT->GetCamera()->SetParent(bot->GetCameraLookAt());
	ENVIRONMENT->GetCamera()->translation = Vector3(0, 2, -10);
	ENVIRONMENT->GetCamera()->rotation = Vector3(0, 0, 0);
	bot->SetTerrain(terrain);
}

TerrainScene::~TerrainScene()
{
	delete terrain;
	delete bot;

}

void TerrainScene::Update()
{
	terrain->Update();
	bot->Update();
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	terrain->Render();
	bot->Render();
}

void TerrainScene::PostRender()
{
}
