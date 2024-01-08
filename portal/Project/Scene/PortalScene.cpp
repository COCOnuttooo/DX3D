#include "Framework.h"
#include "PortalScene.h"
PortalScene::PortalScene()
{
	portal1 = new PortalQuad(Vector2(10,10));
	portal2 = new PortalQuad(Vector2(10,10));
	testQuad = new Quad();
	portal1->GetMaterial()->SetDiffuseMap(&p1Texture, L"Portal1");
	portal2->GetMaterial()->SetDiffuseMap(&p2Texture, L"Portal2");
	portal1->translation = Vector3(-10, 0, 0);
	portal2->translation = Vector3(10, 0, 0);
	portal1->rotation = Vector3(0, XM_PIDIV2, 0);
	portal2->rotation = Vector3(0, -XM_PIDIV2, 0);
	//Environment::GetInstance()->GetP1Camera()->rotation = Vector3(0, XM_PI, 0);
	//Environment::GetInstance()->GetP2Camera()->rotation = Vector3(0, XM_PI, 0);

	cube = new TextureCube();
	
	ENVIRONMENT->GetP1Camera()->SetParent(portal2);
	ENVIRONMENT->GetP2Camera()->SetParent(portal1);
	terrain = new Terrain(L"HeightMap/HeightMap256.png");
	terrain->translation = Vector3(-100, 0, -100);

	terrain->GetMaterial()->SetDiffuseMap(L"Landscape/Dirt2.png");
	terrain->GetMaterial()->SetSpecularMap(L"Landscape/Wall_specular.png");
	terrain->GetMaterial()->SetNormalMap(L"Landscape/Wall_normal.png");
}

PortalScene::~PortalScene()
{
	delete portal1;
	delete portal2;
	delete cube;
	delete testQuad;
	delete terrain;
	
}

void PortalScene::Update()
{
	//Vector3 rotation1 = CAMERA->rotation - portal2->rotation;
	//Vector3 rotation2 =  CAMERA->rotation - portal1->rotation;
	//float distance1 = Vector3(CAMERA->GetGlobalPosition() - portal2->GetGlobalPosition()).Length();
	//float distance2 = Vector3(CAMERA->GetGlobalPosition() - portal1->GetGlobalPosition()).Length();
	//P1CAMERA->translation = -rotation1.GetNormalized() * distance1;
	//P2CAMERA->translation = -rotation2.GetNormalized() * distance2;
	//P1CAMERA->rotation =  rotation1;
	//P2CAMERA->rotation =  rotation2;
	portal1->translation;
	portal1->Update();
	portal2->Update();
	cube->Update();
	testQuad->Update();
	terrain->Update();
}

void PortalScene::PreRender()
{
	cube->Render();
	//terrain->Render();
	//portal1->Render();
	//portal2->Render();
}

void PortalScene::Render()
{
	//terrain->Render();
	cube->Render();
	portal1->Render();
	portal2->Render();
}

void PortalScene::PostRender()
{
	cube->Debug();
}
