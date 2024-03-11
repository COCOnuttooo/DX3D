#include "Framework.h"
#include "WaterScene.h"

WaterScene::WaterScene()
{
	CreateObjects();
	//reflection = new Reflection(floor);
	//refraction = new Refraction(L"Landscape/Wave.dds");

	//floor->GetMaterial()->SetShader(L"26_Reflection");
	//floor->GetMaterial()->SetShader(L"27_Refraction");

	water = new Water(L"Landscape/Wave.dds");
	sky = new SkyBox(L"Landscape/Space.dds");
	shadow = new Shadow(2048,2048);

	LightData& light = ENVIRONMENT->GetLightBuffer()->data.lights[0];

	light.position = { 0,3, -3 };
	light.type = 1;
	light.range = 2000;
}

WaterScene::~WaterScene()
{
	delete floor;
	delete knight;
	delete sphere;
	delete bunny;
	delete shadow;
	delete colSphere;
	//delete reflection;
	//delete refraction;
	delete water;
	delete sky;
	//delete material;
	//delete vertexBuffer;
}

void WaterScene::Update()
{
	sky->Update();
	floor->Update();
	knight->Update();
	sphere->Update();
	bunny->Update();
	colSphere->Update();
	//water->Update();
	//reflection->Update();
	//refraction->Update();
}

void WaterScene::PreRender()
{
	//reflection->SetPreRender();
	//refraction->SetPreRender();
	//water->SetReflection();
	//sky->Render();
	//knight->Render();
	//sphere->Render();
	//bunny->Render();

	//water->SetRefraction();
	//sky->Render();
	//knight->Render();
	//sphere->Render();
	//bunny->Render();
	sky->Render();
	shadow->SetPreRender();
	knight->Render();
	sphere->Render();
	bunny->Render();
	//gBuffer->SetMultiRenderTarget();

}

void WaterScene::Render()
{
	sky->Render();
	//water->Render();
	//reflection->SetRender();
	//refraction->SetRender();
	shadow->SetRender();
	floor->Render();
	knight->Render();
	sphere->Render();
	bunny->Render();

}

void WaterScene::PostRender()
{
	//knight->Debug();
	//sphere->Debug();
	//bunny->Debug();
	//floor->Debug();
	//water->Debug();
	//refraction->Debug();
	shadow->PostRender();
	colSphere->Debug();
}

void WaterScene::CreateObjects()
{
	colSphere = new ColliderSphere();
	floor = new Quad();
	floor->SetName("Floor");
	floor->scale *= 30;
	floor->rotation.x = XM_PIDIV2;
	knight = new ModelAnimator("Knight");
	knight->ReadClip("Hip Hop Dancing");
	knight->translation.y = 0;
	sphere = new Sphere;
	sphere->SetName("Sphere");
	sphere->translation = Vector3(3, 1, 3);
	sphere->GetMaterial()->SetDiffuseMap(L"Landscape/FieldStone_DM.tga");
	sphere->GetMaterial()->SetSpecularMap(L"Landscape/FieldStone_SM.tga");
	sphere->GetMaterial()->SetNormalMap(L"Landscape/FieldStone_NM.tga");
	floor->translation.y += 0.1;
	bunny = new Model("StanfordBunny");
	bunny->SetParent(colSphere);

	floor->GetMaterial()->SetShader(L"29_Shadow");
	knight->SetShader(L"16_Light");
	sphere->GetMaterial()->SetShader(L"16_Light");
	bunny->SetShader(L"16_Light");
}
