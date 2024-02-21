#include "Framework.h"
#include "LightScene.h"
LightScene::LightScene()
{
	floor = new Quad();
	floor->SetName("Floor");
	floor->GetMaterial()->SetShader(L"16_Light");
	floor->scale *= 30;
	floor->rotation.x = XM_PIDIV2;
	knight = new ModelAnimator("Knight");
	knight->ReadClip("Hip Hop Dancing");
	knight->SetShader(L"16_Light");
	knight->translation.y = 0;
	sphere = new Sphere;
	sphere->SetName("Sphere");
	sphere->GetMaterial()->SetShader(L"16_Light");
	sphere->translation = Vector3(3,1,3);
	sphere->GetMaterial()->SetDiffuseMap(L"Landscape/FieldStone_DM.tga");
	sphere->GetMaterial()->SetSpecularMap(L"Landscape/FieldStone_SM.tga");
	sphere->GetMaterial()->SetNormalMap(L"Landscape/FieldStone_NM.tga");
	floor->translation.y += 0.1; 
	bunny = new Model("StanfordBunny");
	bunny->SetShader(L"16_Light");
}

LightScene::~LightScene()
{
	delete floor;
	delete knight;
	delete sphere;
	delete bunny;
}

void LightScene::Update()
{
	floor->Update();
	knight->Update();
	sphere->Update();
	bunny->Update();
}

void LightScene::PreRender()
{
	
}

void LightScene::Render()
{
	floor->Render();
	knight->Render();
	sphere->Render();
	bunny->Render(false);
}

void LightScene::PostRender()
{
	floor->Debug();
	knight->Debug();
	sphere->Debug();
	bunny->Debug();
}
