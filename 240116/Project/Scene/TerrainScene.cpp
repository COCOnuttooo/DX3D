#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"HeightMap/HWHeight.png", L"HeightMap/HWAlpha.png");

	terrain->SetSecondDiffuseMap(L"Landscape/Box.png");

	terrain->GetMaterial()->Load(L"_TextData/Homework.mat");
	terrain->GetMaterial()->CreateShader(L"08_Terrain");
	//terrain->GetMaterial()->SetDiffuseMap(L"Landscape/FieldStone_DM.tga");
	//terrain->GetMaterial()->SetNormalMap(L"Landscape/FieldStone_NM.tga");
	//terrain->GetMaterial()->SetSpecularMap(L"Landscape/FieldStone_SM.tga");

	cube = new Cube;

	//terrain->translation.x = -20;
	//terrain->translation.z = -20;

	//terrain->scale.x *= 2.0f;
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

	//cube->translation.y = terrain->GetHeight(cube->translation);

	cube->translation.y = LERP(cube->translation.y, terrain->GetHeight(cube->translation), 20 * DELTA_TIME) + cube->GetGlobalScale().y * 0.5f;
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
	terrain->GetMaterial()->Debug();
}
