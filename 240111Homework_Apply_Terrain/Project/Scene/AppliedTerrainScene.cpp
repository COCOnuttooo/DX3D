#include "Framework.h"
#include "AppliedTerrainScene.h"

AppliedTerrainScene::AppliedTerrainScene()
{
	terrain = new Terrain(L"HeightMap/homeworkHeight.png");
	terrain->LoadMaterial(L"_TextData/homework.mat");
	//terrain->GetMaterial()->Load(L"_TextData/homework.mat");
	terrain->LoadAlphaMap(L"HeightMap/homeworkAlpha.png");
	terrain->LoadSecondDiffuseMap(L"Solid/Black.png");

}

AppliedTerrainScene::~AppliedTerrainScene()
{
	delete terrain;
}

void AppliedTerrainScene::Update()
{
	terrain->Update();
}

void AppliedTerrainScene::PreRender()
{
}

void AppliedTerrainScene::Render()
{
	terrain->Render();
}

void AppliedTerrainScene::PostRender()
{
	terrain->GetMaterial()->Debug();
}

