#include "Framework.h"
#include "DeferredRenderScene.h"
DeferredRenderScene::DeferredRenderScene()
{
	CreateObjects();
	gBuffer = new GeometryBuffer;
	material = new Material(L"20_DeferredRender");
	vector<UINT> vertices = { 0,1,2,3 };

	vertexBuffer = new VertexBuffer(vertices);
}

DeferredRenderScene::~DeferredRenderScene()
{
	delete floor;
	delete knight;
	delete sphere;
	delete bunny;

	delete gBuffer;

	delete material;
	delete vertexBuffer;
}

void DeferredRenderScene::Update()
{
	floor->Update();
	knight->Update();
	sphere->Update();
	bunny->Update();
}

void DeferredRenderScene::PreRender()
{
	gBuffer->SetMultiRenderTarget();

	knight->Render();
	sphere->Render();
	bunny->Render();
	floor->Render();
}

void DeferredRenderScene::Render()
{
	gBuffer->SetSRVs();
	vertexBuffer->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		material->Set();


	DC->Draw(4, 0);
	//knight->Render();
	//sphere->Render();
	//bunny->Render();
	//floor->Render();
}

void DeferredRenderScene::PostRender()
{
	gBuffer->PostRender();
	knight->Debug();
	sphere->Debug();
	 bunny->Debug();
	 floor->Debug();
}

void DeferredRenderScene::CreateObjects()
{
	floor = new Quad();
	floor->SetName("Floor");
	floor->GetMaterial()->SetShader(L"19_GBuffer");
	floor->scale *= 30;
	floor->rotation.x = XM_PIDIV2;
	knight = new ModelAnimator("Knight");
	knight->ReadClip("Hip Hop Dancing");
	knight->SetShader(L"19_GBuffer");
	knight->translation.y = 0;
	sphere = new Sphere;
	sphere->SetName("Sphere");
	sphere->GetMaterial()->SetShader(L"19_GBuffer");
	sphere->translation = Vector3(3, 1, 3);
	sphere->GetMaterial()->SetDiffuseMap(L"Landscape/FieldStone_DM.tga");
	sphere->GetMaterial()->SetSpecularMap(L"Landscape/FieldStone_SM.tga");
	sphere->GetMaterial()->SetNormalMap(L"Landscape/FieldStone_NM.tga");
	floor->translation.y += 0.1;
	bunny = new Model("StanfordBunny");
	bunny->SetShader(L"19_GBuffer");
}
