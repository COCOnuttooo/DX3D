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

	floor->translation.y += 0.1;
}

LightScene::~LightScene()
{
	delete floor;
	delete knight;
	delete sphere;
}

void LightScene::Update()
{
	floor->Update();
	knight->Update();
	sphere->Update();
}

void LightScene::PreRender()
{
	
}

void LightScene::Render()
{
	floor->Render();
	knight->Render();
	sphere->Render();
}

void LightScene::PostRender()
{
	floor->Debug();
	knight->Debug();
	sphere->Debug();
}
