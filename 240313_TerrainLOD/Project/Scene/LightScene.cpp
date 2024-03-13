#include "Framework.h"
#include "LightScene.h"

LightScene::LightScene()
{
	floor = new Quad();
	floor->SetName("Floor");
	floor->GetMaterial()->SetShader(L"16_Light");

	floor->scale *= 30.0f;
	floor->rotation.x = XM_PIDIV2;
	floor->translation.y = 0.1f;

	knight = new ModelAnimator("Knight");
	knight->ReadClip("Happy Idle");
	knight->SetShader(L"16_Light");

	sphere = new Sphere();
	sphere->SetName("Sphere");
	sphere->GetMaterial()->SetShader(L"16_Light");
	sphere->translation = { 5, 5, 0 };

	sphere->GetMaterial()->SetDiffuseMap(L"Landscape/FieldStone_DM.tga");
	sphere->GetMaterial()->SetNormalMap(L"Landscape/FieldStone_NM.tga");
	sphere->GetMaterial()->SetSpecularMap(L"Landscape/FieldStone_SM.tga");

	bunny = new Model("StanfordBunny");
	bunny->SetShader(L"16_Light");
	//bunny->scale *= 0.01f;

	depthStencil = new DepthStencil();
	renderTarget = new RenderTarget();

	Texture* texture = Texture::Add(L"Scene", renderTarget->GetSRV());
	//floor->GetMaterial()->SetDiffuseMap(texture);

	sky = new SkyBox(L"Landscape/Space.dds");


	quad1 = new Quad();
	quad1->scale = { WIN_CENTER.x, WIN_CENTER.y, 1.0f };
	quad1->translation = { WIN_CENTER.x / 2, WIN_CENTER.y / 2, 0.0f };
	quad1->GetMaterial()->SetDiffuseMap(texture);
	quad1->GetMaterial()->SetShader(L"18_Sepia");

	quad2 = new Quad();
	quad2->scale = { WIN_CENTER.x, WIN_CENTER.y, 1.0f };
	quad2->translation = { WIN_CENTER.x / 2 * 3, WIN_CENTER.y / 2, 0.0f };
	quad2->GetMaterial()->SetDiffuseMap(texture);
	quad2->GetMaterial()->SetShader(L"17_GrayScale");
}

LightScene::~LightScene()
{
	delete floor ;
	delete knight;
	delete sphere;
	delete bunny;

	delete renderTarget;
	delete depthStencil;

	delete sky;

	delete quad1;
	delete quad2;
}

void LightScene::Update()
{
	floor ->Update();
	knight->Update();
	sphere->Update();
	 bunny->Update();
	   sky->Update();

	 quad1->Update();
	 quad2->Update();
}

void LightScene::PreRender()
{
	renderTarget->Set(depthStencil, Vector4(1, 1, 0, 1));

	   sky->Render();

	 floor->Render();
	knight->Render();
	sphere->Render();
	 bunny->Render();
}

void LightScene::Render()
{
	   sky->Render();

	 floor->Render();
	knight->Render();
	sphere->Render();
	 bunny->Render();
}

void LightScene::PostRender()
{
	floor ->Debug();
	knight->Debug();
	sphere->Debug();
	 bunny->Debug();
	 
	 quad1->Render();
	 quad2->Render();
}
