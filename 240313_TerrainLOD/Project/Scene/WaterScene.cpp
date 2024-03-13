#include "Framework.h"
#include "WaterScene.h"

WaterScene::WaterScene()
{
	CreateObjects();

	//reflection = new Reflection(floor);
	//refraction = new Refraction(L"Landscape/Wave.dds");

	//floor->GetMaterial()->SetShader(L"27_Refraction");

	sky = new SkyBox(L"Landscape/Space.dds");

	water = new Water(L"Landscape/Wave.dds");

	shadow = new Shadow(2048, 2048);

	LightData& light = ENVIRONMENT->GetLightBuffer()->data.lights[0];

	light.type = 1;
	light.position = { 0, 100, 10 };
	light.range = 2000.0f;

	terrain = new Terrain(L"HeightMap/HeightMap.png");
	terrain->GetMaterial()->SetDiffuseMap(L"Landscape/Dirt.png");
	terrain->GetMaterial()->SetShader(L"29_Shadow");
}

WaterScene::~WaterScene()
{
	delete floor;
	delete knight;
	delete sphere;
	delete bunny;

	//delete reflection;
	//delete refraction;

	delete sky;
	delete water;

	delete shadow;

	delete terrain;
}

void WaterScene::Update()
{
	//reflection->Update();
	//refraction->Update();

	//water->Update();
	
	 floor->Update();
	knight->Update();
	sphere->Update();
	 bunny->Update();

	 sky->Update();
}

void WaterScene::PreRender()
{
	//reflection->SetPreRender();
	//refraction->SetPreRender();

	//water->SetReflection();

	//   sky->Render();
	//knight->Render();
	//sphere->Render();
	// bunny->Render();

	//water->SetRefraction();

	 //   sky->Render();
	 //floor->Render();

	shadow->SetPreRender();
	 knight->Render();
	 sphere->Render();
	  bunny->Render();
}

void WaterScene::Render()
{
	   sky->Render();

	//reflection->SetRender();
	//refraction->SetRender();

	// water->Render();

	shadow->SetRender();

	//terrain->Render();


	floor->Render();
	knight->Render();
	sphere->Render();
	 bunny->Render();
}

void WaterScene::PostRender()
{
	//reflection->PostRender();
	//refraction->PostRender();
	//refraction->Debug();
	//water->Debug();
	shadow->PostRender();

	knight->Debug();
}

void WaterScene::CreateObjects()
{
	floor = new Quad();
	floor->SetName("Floor");

	floor->scale *= 30.0f;
	floor->rotation.x = XM_PIDIV2;
	floor->translation.y = 0.1f;

	knight = new ModelAnimator("Knight");
	knight->ReadClip("Happy Idle");

	sphere = new Sphere();
	sphere->SetName("Sphere");
	sphere->translation = { 5, 5, 0 };

	sphere->GetMaterial()->SetDiffuseMap(L"Landscape/FieldStone_DM.tga");
	sphere->GetMaterial()->SetNormalMap(L"Landscape/FieldStone_NM.tga");
	sphere->GetMaterial()->SetSpecularMap(L"Landscape/FieldStone_SM.tga");

	bunny = new Model("StanfordBunny");


	 floor->GetMaterial()->SetShader(L"29_Shadow");
	 	 		   knight->SetShader(L"16_Light");
	sphere->GetMaterial()->SetShader(L"16_Light");
	                bunny->SetShader(L"16_Light");
}
