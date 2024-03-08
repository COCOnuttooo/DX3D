#include "Framework.h"
#include "WaterScene.h"

WaterScene::WaterScene()
{
	CreateObjects();

	reflection = new Reflection(floor);

	floor->GetMaterial()->SetShader(L"26_Reflection");

	sky = new SkyBox(L"Landscape/Space.dds");
}

WaterScene::~WaterScene()
{
	delete floor;
	delete knight;
	delete sphere;
	delete bunny;

	delete reflection;

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
	reflection->Update();
}

void WaterScene::PreRender()
{
	reflection->SetPreRender();
	sky->Render();
	knight->Render();
	sphere->Render();
	bunny->Render();
	//gBuffer->SetMultiRenderTarget();

}

void WaterScene::Render()
{
	sky->Render();
	reflection->SetRender();

	floor->Render();
	knight->Render();
	sphere->Render();
	bunny->Render();

}

void WaterScene::PostRender()
{
	knight->Debug();
	sphere->Debug();
	bunny->Debug();
	floor->Debug();
	reflection->PostRender();
}

void WaterScene::CreateObjects()
{
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


	floor->GetMaterial()->SetShader(L"16_Light");
	knight->SetShader(L"16_Light");
	sphere->GetMaterial()->SetShader(L"16_Light");
	bunny->SetShader(L"16_Light");
}
