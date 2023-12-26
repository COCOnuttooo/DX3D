#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"HeightMap/HeightMap.png");
	terrain->GetMaterial()->SetDiffuseMap(L"Landscape/Dirt3.png");
}

TerrainScene::~TerrainScene()
{
	delete terrain;
}

void TerrainScene::Update()
{
	terrain->Update();
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	terrain->Render();

}

void TerrainScene::PostRender()
{
}
